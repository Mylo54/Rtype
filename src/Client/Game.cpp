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
    reg.registerComponents(eng::SparseArray<eng::Velocity>());
    reg.registerComponents(eng::SparseArray<eng::Position>());
    reg.registerComponents(eng::SparseArray<eng::Drawable>());
    reg.registerComponents(eng::SparseArray<eng::Sound>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<eng::Writable>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
    reg.registerComponents(eng::SparseArray<rtp::Button>());
    reg.registerComponents(eng::SparseArray<eng::Music>());
    reg.registerComponents(eng::SparseArray<rtp::Bonus>());
}

void rtp::Game::_addMusic(eng::Registry &reg, std::string filepath)
{
    eng::Entity music = reg.spawnEntity();

    reg.addComponent<eng::Music>(music, eng::Music(filepath, true));
}

eng::Entity rtp::Game::addPlayer(eng::Registry &reg, int playerId, int syncId)
{
    eng::Entity player = reg.spawnEntity();

    reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    reg.addComponent<eng::Velocity>(player, eng::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    reg.addComponent<eng::Drawable>(player, eng::Drawable("assets/players.png", 1, rect, 0.10));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    reg.addComponent<rtp::RectCollider>(player, rtp::RectCollider(40, 16));

    std::cout << "You are player " << playerId << std::endl;
    return player;
}

eng::Entity rtp::Game::_addEnemy(eng::Registry &reg)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    reg.addComponent<eng::Position>(enemy, eng::Position(1920 + (rand() % 2000), rand() % 1080, 0));
    reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-100, 0));
    reg.addComponent<eng::Drawable>(enemy, eng::Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.10));
    reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
    reg.addComponent<rtp::RectCollider>(enemy, rtp::RectCollider(40*scale, 16*scale));

    reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

void rtp::Game::_addScore(eng::Registry &reg)
{
    eng::Entity score = reg.spawnEntity();

    reg.addComponent<eng::Position>(score, eng::Position(850, 0, 0));
    reg.addComponent<eng::Writable>(score, eng::Writable("score", "SCORE:000 000", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::Game::_addBackgrounds(eng::Registry &reg)
{
    for (int i = 0; i < 6; i++) {
        eng::Entity bg = reg.spawnEntity();
        reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 0));
        if (i < 2) {
            reg.addComponent<eng::Velocity>(bg, eng::Velocity(-400, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/foreground.png"));
        } else if (i < 4) {
            reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/middleground.png"));
        } else {
            reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/background.png"));
        }
    }
}