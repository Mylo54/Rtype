/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystem
*/

#include "ClientSystem.hpp"
#include "../GameComponent/Synced.hpp"
#include "../GameComponent/EnemyStats.hpp"
#include "../GameComponent/Controllable.hpp"
#include "../GameComponent/Shooter.hpp"
#include "../GameComponent/PlayerStats.hpp"

rtp::ClientSystem::ClientSystem(rtp::UDPClient &client): _udp(client)
{
}

rtp::ClientSystem::~ClientSystem()
{
}

void rtp::ClientSystem::sendInputData(eng::Registry &reg)
{
    auto &ctrls = reg.getComponents<Controllable>();
    auto &synceds = reg.getComponents<Synced>();
    std::vector<int> data;
    
    for (int i = 0; i < ctrls.size() && i < synceds.size(); i++) {
        if (ctrls[i].has_value() && synceds[i].has_value()) {
            auto &sync = synceds[i].value();
            auto &ctrl = ctrls[i].value();

            data.push_back(25122000);
            data.push_back(sync.id);
            data.push_back(ctrl.xAxis);
            data.push_back(ctrl.yAxis);
            data.push_back(ctrl.shoot);
            data.push_back(ctrl.canonShoot);
            _udp.send(data);
            return;
        }
    }
}

static int getSyncedEntity(eng::Registry &reg, int syncId)
{
    auto &synceds = reg.getComponents<rtp::Synced>();

    for (int i = 0; i < synceds.size(); i++) {
        if (synceds[i].has_value() && synceds[i].value().id == syncId) {
            return (i);
        }
    }
    return (-1);
}

// kill non updated and reset 'isUpdated'
static void killNonUpdated(eng::Registry &reg)
{
    auto &synceds = reg.getComponents<rtp::Synced>();

    for (int i = 0; i < synceds.size(); i++) {
        if (synceds[i].has_value()) {
            if (synceds[i].value().isUpdated)
                synceds[i].value().isUpdated = false;
            else
                reg.killEntity(i);
        }
    }
}

static void completeEnemy(eng::Registry &r, int e, eng::TextureManager &tm)
{
    int type = r.getComponents<rtp::EnemyStats>()[e].value().enemyType;
    float scale = 1;
    if (type == 0) {
        scale = 3;
        r.emplaceComponent<eng::Drawable>(eng::Entity(e), eng::Drawable(tm.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.005));
        r.emplaceComponent<eng::RectCollider>(eng::Entity(e), eng::RectCollider(40 * scale, 16 * scale));
        r.getComponents<eng::Drawable>()[e].value().sprite.setScale(scale, scale);
    }
}

static void completePlayer(eng::Registry &r, int e, eng::TextureManager &tm)
{
    int playerId = r.getComponents<rtp::PlayerStats>()[e].value().playerId;
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    r.addComponent<rtp::Shooter>(eng::Entity(e), rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    r.emplaceComponent<eng::RectCollider>(eng::Entity(e), eng::RectCollider(40, 16));
    auto &smoke = r.addComponent<eng::ParticleEmitter>(eng::Entity(e), eng::ParticleEmitter())[e].value();
    r.addComponent<eng::RigidBody>(eng::Entity(e), eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));

    smoke.setParticleTexture(eng::PARTICLE_TYPE::Sprite, "assets/smokeParticle.png");
    smoke.setBaseSpeed(500, 1000);
    smoke.setLifetime(5);
    smoke.setBaseRotation(260, 280);
    smoke.setEmittingRate(0.01);
    smoke.setMaxNumber(100);
    smoke.isLocal = false;
    smoke.setParticleColor(100, 100, 100, 100);
    r.addComponent<eng::Drawable>(eng::Entity(e), eng::Drawable(tm.getTextureFromFile("assets/players.png"), 1, rect, 0.10));
}

static float midlerp(float a, float b)
{
    return a + 0.5 * (b - a);
}

static void emplacePosition(eng::Registry &r, int e, std::vector<int> &b, int &i)
{
    if (i >= b[1] || b[i] != rtp::position)
        return;
    try {
        auto p = r.getComponents<eng::Position>()[e].value();

        r.emplaceComponent<eng::Position>(eng::Entity(e),
        eng::Position(midlerp(p.x, b[i+1]), midlerp(p.y, b[i+2]), midlerp(p.z, b[i+3])));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Position>(eng::Entity(e), eng::Position(b[i+1], b[i+2], b[i+3]));
    }
    i += 5;
}

static void emplaceVelocity(eng::Registry &r, int e, std::vector<int> &b, int &i)
{
    if (i >= b[1] || b[i] != rtp::velocity)
        return;
    try {
        auto p = r.getComponents<eng::Velocity>()[e].value();

        r.emplaceComponent<eng::Velocity>(eng::Entity(e),
        eng::Velocity(midlerp(p.x, b[i+1]), midlerp(p.y, b[i+2])));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Velocity>(eng::Entity(e), eng::Velocity(b[i+1], b[i+2]));
    }
    i += 4;
}

static void emplacePlayer(eng::Registry &r, int e, std::vector<int> &b, int &i,
bool toBuild, eng::TextureManager &tm)
{
    if (i >= b[1] || b[i] != rtp::playerStats)
        return;
    r.emplaceComponent<rtp::PlayerStats>(e, rtp::PlayerStats(b[i+1], b[i+2], b[i+3]));
    if (toBuild)
        completePlayer(r, e, tm);
    i += 5;
}

static void emplaceEnemy(eng::Registry &r, int e, std::vector<int> &b, int &i,
bool toBuild, eng::TextureManager &tm)
{
    if (i >= b[1] || b[i] != rtp::enemyStats)
        return;
    r.emplaceComponent<rtp::EnemyStats>(e, rtp::EnemyStats(b[i+1], b[i+2]));
    if (toBuild)
        completeEnemy(r, e, tm);
    i += 5;
}

void rtp::ClientSystem::receiveData(eng::Registry &reg, eng::TextureManager &tm)
{
    std::vector<int> data = _udp.receive();
    int current = 0;
    bool toBuild;

    if (data[0] != 25122000)
        return;

    auto &synceds = reg.getComponents<Synced>();    
    for (int i = 2; i < data[1]; i++) {
        if (data[i] == 14052002) {
            current = getSyncedEntity(reg, data[i + 1]);
            toBuild = current < 0;
            if (toBuild) {
                current = reg.spawnEntity().getId();
                reg.addComponent(eng::Entity(current), Synced(data[i + 1]));
            }
        }
        // build / create
        emplacePosition(reg, current, data, i);
        emplacePosition(reg, current, data, i);
        emplaceEnemy(reg, current, data, i, toBuild, tm);
        emplacePlayer(reg, current, data, i, toBuild, tm);
    }
    killNonUpdated(reg);
}