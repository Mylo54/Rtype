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
    r.addComponent<rtp::RectCollider>(bns, rtp::RectCollider(16 * scale, 16 * scale));
    r.addComponent<rtp::Synced>(bns, rtp::Synced(bns.getId()));
    _bonusTimer = _bonusRate;
}

void rtp::ServerSystems::bonusCollisions(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
    auto &players = r.getComponents<PlayerStats>();
    auto &colliders = r.getComponents<RectCollider>();

    for (int i = 0; i < players.size() && i < positions.size() && i < colliders.size(); i++) {
        if (players[i].has_value() && positions[i].has_value() && colliders[i].has_value()) {
            bonusCollision(r, players[i].value(), positions[i].value(), colliders[i].value());
        }
    }
}

void rtp::ServerSystems::bonusCollision(eng::Registry &r, rtp::PlayerStats &playerStats, eng::Position &playerPos, rtp::RectCollider & playerRect)
{
    auto &bonuses = r.getComponents<Bonus>();
    auto &positions = r.getComponents<eng::Position>();
    auto &colliders = r.getComponents<rtp::RectCollider>();

    for (int i = 0; i < bonuses.size() && i < positions.size(); i++) {
        if (bonuses[i].has_value() && positions[i].has_value()) {
            auto &bonus = bonuses[i].value();
            auto &bonusPos = positions[i].value();
            auto &bonusRect = colliders[i].value();
            if (isColliding(bonusPos, bonusRect, playerPos, playerRect))
                collectBonus(r, playerStats, bonus, i);
        }
    }
}

void rtp::ServerSystems::collectBonus(eng::Registry &r, rtp::PlayerStats &playerStats, rtp::Bonus &bonus, int bonusID)
{
    std::cout << "Collecting bonus of type " << bonus.type << std::endl;
    // Changes on player stats
    if (bonus.type == 0)
        playerStats.damage += 1;
    // Destroy bonus
    r.killEntity(bonusID);
    std::cout << "Player damages : " << playerStats.damage << std::endl;
}