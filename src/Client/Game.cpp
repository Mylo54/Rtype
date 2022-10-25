/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Game
*/

#include "Game.hpp"

rtp::Game::Game(eng::RegistryManager &manager) : _manager(manager)
{
    _manager.addRegistry("R2");
    _setupRegistry(_manager.getTop());
    _addBackgrounds(_manager.getTop());
    _addScore(_manager.getTop());
    _addMusic(_manager.getTop(), "assets/music.ogg");
}

rtp::Game::~Game()
{
}

void rtp::Game::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    reg.registerComponents(eng::SparseArray<rtp::AudioSource>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<rtp::Writable>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
    reg.registerComponents(eng::SparseArray<rtp::Button>());
    reg.registerComponents(eng::SparseArray<rtp::Music>());
}

void rtp::Game::_addMusic(eng::Registry &reg, std::string filepath)
{
    eng::Entity music = reg.spawnEntity();

    reg.addComponent<rtp::Music>(music, rtp::Music(filepath, true));
}

eng::Entity rtp::Game::_addPlayer(eng::Registry &reg, int playerId, int syncId)
{
    eng::Entity player = reg.spawnEntity();

    reg.addComponent<rtp::Position>(player, rtp::Position(200, 540, 0));
    reg.addComponent<rtp::Velocity>(player, rtp::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    reg.addComponent<rtp::Drawable>(player, rtp::Drawable("assets/players.png", 1, rect, 0.10));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));

    std::cout << "You are player " << playerId << std::endl;
    return player;
}

eng::Entity rtp::Game::_addEnemy(eng::Registry &reg)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    reg.addComponent<rtp::Position>(enemy, rtp::Position(1920 + (rand() % 2000), rand() % 1080, 0));
    reg.addComponent<rtp::Velocity>(enemy, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Drawable>(enemy, rtp::Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.10));
    reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
    reg.addComponent<rtp::RectCollider>(enemy, rtp::RectCollider(40*scale, 16*scale));

    reg.getComponents<rtp::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

void rtp::Game::_addScore(eng::Registry &reg)
{
    eng::Entity score = reg.spawnEntity();

    reg.addComponent<rtp::Position>(score, rtp::Position(1000, 0, 0));
    reg.addComponent<rtp::Writable>(score, rtp::Writable("score", "SCORE:000 000"));
}

void rtp::Game::_addBackgrounds(eng::Registry &reg)
{
    for (int i = 0; i < 6; i++) {
        eng::Entity bg = reg.spawnEntity();
        reg.addComponent<rtp::Position>(bg, rtp::Position((i % 2) * 1920, 0, 0));
        if (i < 2) {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-20, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/foreground.png"));
        } else if (i < 4) {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-10, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/middleground.png"));
        } else {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-5, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/background.png"));
        }
    }
}