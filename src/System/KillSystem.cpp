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

void rtp::KillSystem::killDeadEnemies(eng::Registry &r, int &score, rtp::TextSystem &text, float delta, eng::TextureManager &texture)
{
    auto &ennemies = r.getComponents<EnemyStats>();
    auto &positions = r.getComponents<eng::Position>();
    auto &rects = r.getComponents<eng::RectCollider>();

    for (int i = 0; i < ennemies.size(); i++)
        if (ennemies[i].has_value() && ennemies[i].value().enemyType == 4) {
            ennemies[i].value().lifeTime -= delta;
            if (ennemies[i].value().lifeTime <= 0)
                r.killEntity(eng::Entity(i));
        }

    for (int i = 0; i < ennemies.size() && i < positions.size() && i < rects.size(); i++) {
        if (ennemies[i].has_value() && positions[i].has_value() && rects[i].has_value()) {
            if (ennemies[i].value().health <= 0 || ennemies[i].value().lifeTime <= 0) {
                if (ennemies[i].value().enemyType == 1) {
                    score += 10;
                    explosion(r, texture, positions[i].value().x, positions[i].value().y, rects[i].value().width, 1);
                }
                if (ennemies[i].value().enemyType == 2) {
                    score += 30;
                    explosion(r, texture, positions[i].value().x, positions[i].value().y, rects[i].value().width, 2);
                }
                if (ennemies[i].value().enemyType == 3)
                    score += 10000;
                r.killEntity(eng::Entity(i));
                std::stringstream s;
                s << "SCORE : ";
                // s << ((score / 1000 > 10) ? "0" : "00") <<  score / 100 << " ";
                // s << ((score % 1000 > 10) ? "0" : "00") << score % 100;
                s << score;
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

void rtp::KillSystem::explosion(eng::Registry &reg, eng::TextureManager &texture, float x, float y, float size, int explosionType)
{
    eng::Entity explosion = reg.spawnEntity();
    std::string asset;
    size /= 200;

    if (explosionType == 1) asset = "assets/explosion.png";
    if (explosionType == 2) asset = "assets/explosion2.png";
    reg.addComponent<eng::Position>(explosion, eng::Position(x, y , 5));
    reg.addComponent<eng::Velocity>(explosion, eng::Velocity(-(50 + rand() % 100), 0));
    reg.addComponent<eng::Drawable>(explosion, eng::Drawable(texture.getTextureFromFile(asset), 1, sf::IntRect(0, 0, 105, 105), 0.090));
    reg.addComponent<rtp::EnemyStats>(explosion, rtp::EnemyStats(1, 4, 0.8));

    reg.getComponents<eng::Drawable>()[explosion.getId()].value().sprite.setScale(size, size);
}
