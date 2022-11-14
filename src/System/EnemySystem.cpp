/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** EnemySystem
*/

#include "EnemySystem.hpp"

rtp::EnemySystem::EnemySystem()
{
}

rtp::EnemySystem::~EnemySystem()
{
}

eng::Entity rtp::EnemySystem::_addEnemy(eng::Registry &reg, eng::TextureManager &texture, int enemyType)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 7) + 3;

    if (enemyType == 1) {
        reg.addComponent<eng::Position>(enemy, eng::Position(1920, rand() % 1080, 5));
        reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-(50 + rand() % 100), 0));
        reg.addComponent<eng::Drawable>(enemy, eng::Drawable(texture.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.10));
        reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5, 1));
        reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(40*scale, 16*scale));
    }
    if (enemyType == 2) {
        reg.addComponent<eng::Position>(enemy, eng::Position(1920, 80 + rand() % 920, 5));
        reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-(50 + rand() % 100), 0));
        reg.addComponent<eng::Drawable>(enemy, eng::Drawable(texture.getTextureFromFile("assets/flyers2.png"), 3, sf::IntRect(0, 0, 40, 16), 0.10));
        reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(2, 2));
        reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(40*scale, 16*scale));   
    }
    reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

// Bullets are considered as (x, y) points
void rtp::EnemySystem::playerBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < blts.size() && i < poss.size(); i++) {
        if (blts[i].has_value() && poss[i].has_value()) {
            _bulletAgainstEnemy(r, eng::Entity(i));
        }
    }
}

void rtp::EnemySystem::_bulletAgainstEnemy(eng::Registry &r, eng::Entity blt)
{
    auto &enms = r.getComponents<rtp::EnemyStats>();
    auto &poss = r.getComponents<eng::Position>();
    auto &rcts = r.getComponents<eng::RectCollider>();
    auto &p = r.getComponents<eng::Position>()[blt.getId()].value();
    auto &b = r.getComponents<rtp::Bullet>()[blt.getId()].value();

    for (int i = 0; i < enms.size() && i < poss.size() && i < rcts.size(); i++) {
        if (enms[i].has_value() && poss[i].has_value() && rcts[i].has_value()) {
            auto &enm = enms[i].value();
            auto &pos = poss[i].value();
            auto &rct = rcts[i].value();
            if (p.x >= pos.x + rct.offsetX && p.y >= pos.y + rct.offsetY) {
                if (p.x <= pos.x + rct.width + rct.offsetX && p.y <= pos.y + rct.height + rct.offsetY) {
                    enm.health -= b.damage;
                    r.killEntity(blt);
                }
            }
        }
    }
}

void rtp::EnemySystem::enemyCollision(eng::Registry &r, eng::PhysicSystems &physic)
{
    auto &enemies = r.getComponents<rtp::EnemyStats>();
    auto &positions = r.getComponents<eng::Position>();
    auto &colliders = r.getComponents<eng::RectCollider>();
    auto &stats = r.getComponents<rtp::PlayerStats>();

    for (int j = 0; j < stats.size() && j < positions.size() && j < colliders.size(); j++) {
        if (stats[j].has_value() && positions[j].has_value() && colliders[j].has_value())
            for (int i = 0; i < enemies.size() && i < positions.size() && i < colliders.size(); i++) {
                if (enemies[i].has_value() && positions[i].has_value() && colliders[i].has_value()) {
                    auto &enemy = enemies[i].value();
                    auto &enemyPos = positions[i].value();
                    auto &enemyRect = colliders[i].value();
                    // if (isColliding(enemyPos, enemyRect, positions[entity].value(), colliders[entity].value())) {
                    if (physic.areRectColliding(enemyPos, enemyRect, positions[j].value(), colliders[j].value())) {
                        if (enemy.enemyType == 3) {
                            r.killEntity(j);
                            enemy.health -= 50;
                        }
                        else {
                            stats[j].value().lives -= 1;
                            r.killEntity(i);
                        }
                    }
                }
            }
    }
}

void rtp::EnemySystem::spawnEnemies(eng::Registry &reg, float &enemyTimer, int level, float delta, eng::TextureManager &texture)
{
    enemyTimer -= delta;
    int enemyType = 1;
    if (enemyTimer <= 0) {
        if (rand() % 4 == 1) enemyType = 2;
        _addEnemy(reg, texture, enemyType);
        updateTrajectories(reg);
        enemyTimer = 4.5 - level;
        if (enemyTimer <= 0.5) enemyTimer = 0.5;
    }
}

void rtp::EnemySystem::updateTrajectories(eng::Registry &r)
{
    auto &enemies = r.getComponents<rtp::EnemyStats>();
    auto &vels = r.getComponents<eng::Velocity>();

    for (int i = 0; i < enemies.size() && i < vels.size(); i++) {
        if (enemies[i].has_value() && vels[i].has_value()) {
            if (enemies[i].value().enemyType == 2) {
                vels[i].value().y = 100 * ((rand() % 3) - 1);
            }
        }
    }
}

eng::Entity rtp::EnemySystem::_addBoss(eng::Registry &reg, eng::TextureManager &texture)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = 5;

    reg.addComponent<eng::Position>(enemy, eng::Position(1920, 0, 5));
    reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-40, 0));
    reg.addComponent<eng::Drawable>(enemy, eng::Drawable(texture.getTextureFromFile("assets/boss.png"), 0, sf::IntRect(0, 0, 107, 207), 0.10));
    reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(100, 3));
    reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(30*scale, 20*scale, 0, 250));

    reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

void rtp::EnemySystem::bossAnimation(eng::Registry &r)
{
    auto &enemies = r.getComponents<rtp::EnemyStats>();
    auto &vels = r.getComponents<eng::Velocity>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < enemies.size() && i < vels.size() && i < poss.size(); i++) {
        if (enemies[i].has_value() && vels[i].has_value() && poss[i].has_value()) {
            if (enemies[i].value().enemyType == 3 && poss[i].value().x <= 1400) {
                vels[i].value().x = 0;
            }
        }
    }
}

