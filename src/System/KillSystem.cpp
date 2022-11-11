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