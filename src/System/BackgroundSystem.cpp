/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** BackgroundSystem
*/

#include "BackgroundSystem.hpp"

rtp::BackgroundSystem::BackgroundSystem()
{
}

rtp::BackgroundSystem::~BackgroundSystem()
{
}

void rtp::BackgroundSystem::loop(eng::Registry &r)
{
    auto &bgs = r.getComponents<Background>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < bgs.size() && i < poss.size(); i++) {
        if (poss[i].has_value() && bgs[i].has_value()) {
            auto &pos = poss[i].value();
            auto &bg = bgs[i].value();
            if (pos.x <= -1920)
                pos.x = 1920;
        }
    }
}