/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EnemySystem
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::setEnemyRate(float seconds)
{
    _enemyRate = seconds;
}

void rtp::ServerSystems::spawnEnemies(eng::Registry &r)
{
    _enemyTimer -= _getDeltaAsSeconds();

    if (_enemyTimer <= 0) {
        eng::Entity enm = r.spawnEntity();

        float posY = rand() % 1080;
        int scale = 3;

        r.addComponent<eng::Position>(enm, eng::Position(1919, posY, 0));
        r.addComponent<eng::Velocity>(enm, eng::Velocity(-5, 0));
        r.addComponent<rtp::EnemyStats>(enm, rtp::EnemyStats(5, 0));
        r.addComponent<rtp::RectCollider>(enm, rtp::RectCollider(40 * scale, 16 * scale));
        r.addComponent<rtp::Synced>(enm, rtp::Synced(enm.getId()));
        _enemyTimer = _enemyRate;
    }
}

void rtp::ServerSystems::_bulletAgainstEnemy(eng::Registry &r, eng::Entity blt)
{
    auto &enms = r.getComponents<EnemyStats>();
    auto &poss = r.getComponents<eng::Position>();
    auto &rcts = r.getComponents<RectCollider>();
    auto &p = r.getComponents<eng::Position>()[blt.getId()].value();
    auto &b = r.getComponents<Bullet>()[blt.getId()].value();

    for (int i = 0; i < enms.size() && i < poss.size() && i < rcts.size(); i++) {
        if (enms[i].has_value() && poss[i].has_value() && rcts[i].has_value()) {
            auto &enm = enms[i].value();
            auto &pos = poss[i].value();
            auto &rct = rcts[i].value();
            if (p.x >= pos.x && p.y >= pos.y) {
                if (p.x <= pos.x + rct.width && p.y <= pos.y + rct.height) {
                    enm.health -= b.damage;
                    r.killEntity(blt);
                }
            }
        }
    }
}

void rtp::ServerSystems::killDeadEnemies(eng::Registry &r)
{
    auto &enemies = r.getComponents<EnemyStats>();
    auto &positions = r.getComponents<eng::Position>();

    for (int i = 0; i < enemies.size() && i < positions.size(); i++)
        if (enemies[i].has_value() && positions[i].has_value())
            if (enemies[i].value().health <= 0) {
                if (rand() % 5 == 0) {
                    spawnBonus(r, positions[i].value().x, positions[i].value().y);
                }
                r.killEntity(eng::Entity(i));
            }
}

void rtp::ServerSystems::enemyCollision(eng::Registry &r, int entity)
{
    auto &enemies = r.getComponents<EnemyStats>();
    auto &positions = r.getComponents<eng::Position>();
    auto &colliders = r.getComponents<rtp::RectCollider>();
    auto &stats = r.getComponents<rtp::PlayerStats>();

    for (int i = 0; i < enemies.size() && i < positions.size(); i++) {
        if (enemies[i].has_value() && positions[i].has_value()) {
            auto &enemy = enemies[i].value();
            auto &enemyPos = positions[i].value();
            auto &enemyRect = colliders[i].value();
            if (isColliding(enemyPos, enemyRect, positions[entity].value(), colliders[entity].value())) {
                stats[entity].value().lives -= 1;
                r.killEntity(i);
            }
        }
    }
}