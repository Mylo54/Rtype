/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystems
*/

#include "ServerSystems.hpp"

rtp::ServerSystems::ServerSystems(boost::asio::ip::udp::socket &socket,
    std::mutex &mutex, std::vector<std::vector<int>> &listDataRec,
    std::vector<boost::asio::ip::udp::endpoint> &endpoints) : _socket(socket),
    _mutex(mutex), _listDataRec(listDataRec), _endpoints(endpoints)
{
    _lastUpdate = std::chrono::steady_clock::now();
}

rtp::ServerSystems::~ServerSystems()
{
}

void rtp::ServerSystems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
    auto &velocities = r.getComponents<eng::Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += (vel.value().x * float(_delta) / 1000000 * 20);
            pos.value().y += (vel.value().y * float(_delta) / 1000000 * 20);
        }
    }
}

void rtp::ServerSystems::controlMovementSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<eng::Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * _getDeltaAsSeconds() * 20 * 2;
            vel.value().x += (vel.value().x > 0) ? -(_getDeltaAsSeconds() * 20) : 0;
            vel.value().x += (vel.value().x < 0) ? _getDeltaAsSeconds() * 20 : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * _getDeltaAsSeconds() * 20 * 2;
            vel.value().y += (vel.value().y > 0) ? -(_getDeltaAsSeconds() * 20) : 0;
            vel.value().y += (vel.value().y < 0) ? _getDeltaAsSeconds() * 20 : 0;
        }
    }
}

int rtp::ServerSystems::_getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<Synced>();

    for (int i = 0; i < synceds.size(); i++)
        if (synceds[i].has_value() == true)
            if (synceds[i].value().id == syncId)
                return i;
    return -1;
}

void rtp::ServerSystems::killOutOfBounds(eng::Registry &r)
{
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < poss.size(); i++) {
        if (poss[i].has_value()) {
            auto pos = poss[i].value();

            if (pos.x > 1920 || pos.x < -1)
                r.killEntity(eng::Entity(i));
            else if (pos.y > 1080 || pos.y < -1)
                r.killEntity(eng::Entity(i));
        }
    }
}

void rtp::ServerSystems::collisions(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
    auto &players = r.getComponents<PlayerStats>();
    auto &colliders = r.getComponents<eng::RectCollider>();

    for (int i = 0; i < players.size() && i < positions.size() && i < colliders.size(); i++) {
        if (players[i].has_value() && positions[i].has_value() && colliders[i].has_value()) {
            // bonusCollision(r, players[i].value(), positions[i].value(), colliders[i].value());
            bonusCollision(r, i);
            enemyCollision(r, i);
        }
    }
}

bool rtp::ServerSystems::isColliding(eng::Position &pos1, eng::RectCollider & rect1, eng::Position &pos2, eng::RectCollider & rect2)
{
    if (pos1.x > (pos2.x + rect2.width)) return false;
    if ((pos1.x + rect1.width) < pos2.x) return false;
    if (pos1.y > (pos2.y + rect2.height)) return false;
    if ((pos1.y + rect1.height) < pos2.y) return false;
    return true;
}