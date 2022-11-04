/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** BonusSystem
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::setBonusRate(float seconds)
{
    _bonusRate = seconds;
}

void rtp::ServerSystems::spawnBonus(eng::Registry &r, float x, float y)
{
    eng::Entity bns = r.spawnEntity();

    float posY = rand() % 1080;
    float velX = (rand() % 5) * (-1);
    float velY = (rand() % 5) - 2;
    int scale = 3;

    r.addComponent<eng::Position>(bns, eng::Position(x, y, 0));
    r.addComponent<eng::Velocity>(bns, eng::Velocity(velX, velY));
    r.addComponent<rtp::Bonus>(bns, rtp::Bonus(0));
    r.addComponent<eng::RectCollider>(bns, eng::RectCollider(16 * scale, 16 * scale));
    r.addComponent<rtp::Synced>(bns, rtp::Synced(bns.getId()));
    _bonusTimer = _bonusRate;
}

void rtp::ServerSystems::bonusCollision(eng::Registry &r, int entity)
{
    auto &bonuses = r.getComponents<Bonus>();
    auto &positions = r.getComponents<eng::Position>();
    auto &colliders = r.getComponents<eng::RectCollider>();
    auto &stats = r.getComponents<rtp::PlayerStats>();

    for (int i = 0; i < bonuses.size() && i < positions.size(); i++) {
        if (bonuses[i].has_value() && positions[i].has_value()) {
            auto &bonus = bonuses[i].value();
            auto &bonusPos = positions[i].value();
            auto &bonusRect = colliders[i].value();
            if (isColliding(bonusPos, bonusRect, positions[entity].value(), colliders[entity].value()))
                collectBonus(r, entity, i);
        }
    }
}

void rtp::ServerSystems::collectBonus(eng::Registry &r, int player, int bonus)
{
    auto &bonuses = r.getComponents<Bonus>();
    auto &positions = r.getComponents<eng::Position>();
    auto &colliders = r.getComponents<eng::RectCollider>();
    auto &stats = r.getComponents<rtp::PlayerStats>();
    // Changes on player stats
    if (bonuses[bonus].value().type == 0)
        stats[player].value().damage += 1;
    // Destroy bonus
    r.killEntity(bonus);
}