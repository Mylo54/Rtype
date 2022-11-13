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

void rtp::KillSystem::killDeadEnemies(eng::Registry &r, int &score, rtp::TextSystem &text)
{
    auto &ennemies = r.getComponents<EnemyStats>();

    for (int i = 0; i < ennemies.size(); i++) {
        if (ennemies[i].has_value()) {
            if (ennemies[i].value().health <= 0) {
                r.killEntity(eng::Entity(i));
                score += 10;
                std::stringstream s;
                s << "score:";
                s << ((score / 100 > 10) ? "0" : "00") <<  score / 100 << " ";
                s << ((score % 100 > 10) ? "0" : "00") << score % 100;
                // std::cout << "Score : " << s.str() << std::endl;
                text.setText(r, s.str(), "score", rtp::TextSystem::CHAT);
            }
        }
    }
}

void rtp::KillSystem::killDeadPlayers(eng::Registry &r, rtp::TextSystem &text)
{
    auto &players = r.getComponents<rtp::PlayerStats>();

    for (int i = 0; i < players.size(); i++) {
        if (players[i].has_value()) {
            if (players[i].value().lives <= 0) {
                r.killEntity(eng::Entity(i));
            }
        }
    }
}

bool rtp::KillSystem::allPlayerKilled(eng::Registry &r)
{
    bool allDead = true;
    auto &players = r.getComponents<rtp::PlayerStats>();

    for (int i = 0; i < players.size(); i++) {
        if (players[i].has_value())
            if (players[i].value().lives > 0)
                allDead = false;
    }
    return allDead;
}