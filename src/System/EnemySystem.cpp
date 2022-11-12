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

eng::Entity rtp::EnemySystem::_addEnemy(eng::Registry &reg, eng::TextureManager &texture)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    reg.addComponent<eng::Position>(enemy, eng::Position(1920, rand() % 1080, 5));
    reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-100, 0));
    reg.addComponent<eng::Drawable>(enemy, eng::Drawable(texture.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.10));
    // reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
    reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(40*scale, 16*scale));

    reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}