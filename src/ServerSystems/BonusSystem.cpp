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
    _bonusTimer -= _getDeltaAsSeconds();

    if (_bonusTimer <= 0) {
        eng::Entity bns = r.spawnEntity();

        float posY = rand() % 1080;
        float velX = (rand() % 5) * (-1);
        float velY = (rand() % 5) - 2;
        int scale = 3;

        r.addComponent<rtp::Position>(bns, rtp::Position(x, y, 0));
        r.addComponent<rtp::Velocity>(bns, rtp::Velocity(velX, velY));
        r.addComponent<rtp::Bonus>(bns, rtp::Bonus(0));
        r.addComponent<rtp::RectCollider>(bns, rtp::RectCollider(16 * scale, 16 * scale));
        r.addComponent<rtp::Synced>(bns, rtp::Synced(bns.getId()));
        _bonusTimer = _bonusRate;
    }
}