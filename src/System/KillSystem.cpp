/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** KillSystem
*/

#include "KillSystem.hpp"

rtp::KillSystem::KillSystem()
{
}

rtp::KillSystem::~KillSystem()
{
}

void rtp::KillSystem::killOutOfBounds(eng::Registry &r)
{
    auto &poss = r.getComponents<eng::Position>();
    auto &drawables = r.getComponents<eng::Drawable>();

    for (int i = 0; i < poss.size() && i < drawables.size(); i++) {
        if (poss[i].has_value() && drawables[i].has_value()) {
            auto pos = poss[i].value();
            auto drw = drawables[i].value();
            if (!drw.protect) {
                if (pos.x > 1920 || pos.x < (-1 * drw.sizeX))
                    r.killEntity(eng::Entity(i));
                else if (pos.y > 1080 || pos.y < (-1 * drw.sizeY))
                    r.killEntity(eng::Entity(i));
            }
        }
    }
}

void rtp::KillSystem::killBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < blts.size(); i++) {
        if (blts[i].has_value()) {
            auto blt = blts[i].value();
            auto pos = poss[i].value();
            if (pos.x > 1920 || pos.x < -1) {
                r.killEntity(eng::Entity(i));
            }
            else if (pos.y > 1080 || pos.y < -1)
                r.killEntity(eng::Entity(i));
        }
    }
}

void rtp::KillSystem::killDeadEnemies(eng::Registry &r)
{
    auto &ennemies = r.getComponents<EnemyStats>();

    for (int i = 0; i < ennemies.size(); i++) {
        if (ennemies[i].has_value()) {
            if (ennemies[i].value().health <= 0) {
                r.killEntity(eng::Entity(i));
                // _score += 10;
                // std::stringstream s;
                // s << "score:";
                // s << ((_score / 100 > 10) ? "0" : "00") <<  _score / 100 << " ";
                // s << ((_score % 100 > 10) ? "0" : "00") << _score % 100;
                // setText(r, s.str(), "score", CHAT);
            }
        }

    }
}