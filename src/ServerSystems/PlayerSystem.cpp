/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** PlayerSystem
*/

#include "ServerSystems.hpp"

// Max speed should be defined elsewhere...
void rtp::ServerSystems::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<eng::Position>();
    auto &ves = r.getComponents<eng::Velocity>();
    auto &pls = r.getComponents<PlayerStats>();
    float maxSpeed = 300;

    for (int i = 0; i < pos.size() && i < ves.size() && i < pls.size(); i++) {
        if (pos[i].has_value() && ves[i].has_value() && pls[i].has_value()) {
            auto &position = pos[i].value();
            auto &velocity = ves[i].value();
            auto &playerSt = pls[i].value();

            position.x = (position.x >= 1860) ? 1860 : position.x;
            position.x = (position.x < 0) ? 0 : position.x;
            position.y = (position.y >= 982) ? 982 : position.y;
            position.y = (position.y < 0) ? 0 : position.y;

            velocity.x = (velocity.x >= maxSpeed) ? maxSpeed : velocity.x;
            velocity.x = (velocity.x <= -maxSpeed) ? -maxSpeed : velocity.x;
            velocity.y = (velocity.y >= maxSpeed) ? maxSpeed : velocity.y;
            velocity.y = (velocity.y <= -maxSpeed) ? -maxSpeed : velocity.y;
        }
    }
}

void rtp::ServerSystems::controlFireSystem(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();
    auto &playerStats = r.getComponents<PlayerStats>();
    auto &positions = r.getComponents<eng::Position>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value() && ctrl.value().shoot) {
            eng::Entity bullet = r.spawnEntity();
            auto &pos = positions[i].value();
            auto &plyr = playerStats[i].value();
            
            ctrl.value().shoot = false;
            ctrl.value().hasShot = true;
            r.addComponent(bullet, eng::Velocity(300, 0));
            r.addComponent(bullet, eng::Position(pos.x + 65, pos.y + 25, pos.z));
            r.addComponent(bullet, rtp::Bullet(2));
        }
    }
}

// Bullets are considered as (x, y) points
void rtp::ServerSystems::playerBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < blts.size() && i < poss.size(); i++) {
        if (blts[i].has_value() && poss[i].has_value()) {
            _bulletAgainstEnemy(r, eng::Entity(i));
        }
    }
}