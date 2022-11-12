/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Game
*/

#include "Game.hpp"

rtp::Game::Game(rtp::scene_package_t pack): AScene(pack)
{
}

rtp::Game::~Game()
{
}

void rtp::Game::setupScene()
{
    setupRegistry();
    _addBackgrounds();
    _addScore();
    _addMusic();
    addPlayer(1, 0);
}

void rtp::Game::setupRegistry()
{
    _reg.registerComponents(eng::SparseArray<eng::Velocity>());
    _reg.registerComponents(eng::SparseArray<eng::Position>());
    _reg.registerComponents(eng::SparseArray<eng::Drawable>());
    _reg.registerComponents(eng::SparseArray<eng::Sound>());
    _reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    _reg.registerComponents(eng::SparseArray<eng::Writable>());
    _reg.registerComponents(eng::SparseArray<eng::Music>());
    _reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    _reg.registerComponents(eng::SparseArray<eng::RigidBody>());
    _reg.registerComponents(eng::SparseArray<rtp::Background>());
    _reg.registerComponents(eng::SparseArray<rtp::Button>());
    _reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    _reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    _reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    _reg.registerComponents(eng::SparseArray<rtp::Bullet>());
}

void rtp::Game::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape")) {
        _sceneEvent = 2;
        _sceneNumber = 2;
    }
    // Debug pour end screen
    // if (_input.isActionJustPressed("ui_left")) {
    //     _sceneEvent = 2;
    //     _sceneNumber = 6;
    // }
    // if (_input.isActionJustPressed("ui_right")) {
    //     _sceneEvent = 2;
    //     _sceneNumber = 7;
    // }

    //Controls
    if (_graphic.isWindowFocused())
        _playerSystem.control(_reg, _input);
    _playerSystem.controlMovement(_reg, _input, _graphic.getDeltaSeconds());
    _physic.applyGravity(_reg);

    _physic.applyVelocities(_reg);
    _playerSystem.limitPlayer(_reg);
    // Shooting
    _playerSystem.controlFireSystem(_reg, _graphic.getDeltaSeconds());
    _playerSystem.shootSystem(_reg);

    _killSystem.killOutOfBounds(_reg);
    _killSystem.killBullets(_reg);
    // Play sounds & music
    _audio.playMusic(_reg);
    _audio.playSound(_reg);

    // clear, draw & display
    _graphic.clear();
    _graphic.animateSystem(_reg);
    _graphic.particleSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.writeSystem(_reg);
    _graphic.display();
}

void rtp::Game::_addMusic()
{
    eng::Entity music = _reg.spawnEntity();

    _reg.addComponent<eng::Music>(music, eng::Music("assets/music.ogg", true));
}

eng::Entity rtp::Game::addPlayer(int playerId, int syncId)
{
    eng::Entity player = _reg.spawnEntity();
    std::stringstream name;
    name << "P" << playerId;

    _reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    _reg.addComponent<eng::Velocity>(player, eng::Velocity());
    _reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    _reg.addComponent<eng::Drawable>(player, eng::Drawable(_texture.getTextureFromFile("assets/players.png"), 1, rect, 0.10));
    _reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    // reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    _reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    _reg.addComponent<eng::RectCollider>(player, eng::RectCollider(40, 16));
    _reg.addComponent<eng::RigidBody>(player, eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));
    _reg.addComponent<eng::Writable>(player, eng::Writable("Player name", name.str(), "assets/MetroidPrimeHunters.ttf", 30, sf::Color::Yellow, sf::Text::Regular, 20, -35));
    auto &smoke = _reg.addComponent<eng::ParticleEmitter>(player, eng::ParticleEmitter())[player.getId()].value();

    smoke.setParticleTexture(eng::PARTICLE_TYPE::Sprite, "assets/smokeParticle.png");
    smoke.setBaseSpeed(500, 1000);
    smoke.setLifetime(5);
    smoke.setBaseRotation(260, 280);
    smoke.setEmittingRate(0.01);
    smoke.setMaxNumber(100);
    smoke.isLocal = false;
    smoke.setParticleColorRandom(true);

    std::cout << "You are player " << playerId << std::endl;
    return player;
}

eng::Entity rtp::Game::_addEnemy()
{
    eng::Entity enemy = _reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    _reg.addComponent<eng::Position>(enemy, eng::Position(1920 + (rand() % 2000), rand() % 1080, 0));
    _reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-100, 0));
    _reg.addComponent<eng::Drawable>(enemy, eng::Drawable(_texture.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.10));
    // reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
    _reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(40*scale, 16*scale));

    _reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

void rtp::Game::_addScore()
{
    eng::Entity score = _reg.spawnEntity();

    _reg.addComponent<eng::Position>(score, eng::Position(850, 0, 0));
    _reg.addComponent<eng::Writable>(score, eng::Writable("score", "SCORE:000 000", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::Game::_addBackgrounds()
{
    for (int i = 0; i < 12; i++) {
        eng::Entity bg = _reg.spawnEntity();
        if (i >= 0 && i < 2) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 10));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 2 && i < 4) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 9));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/fog1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 4 && i < 6) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 8));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-300, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/stars1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 6 && i < 8) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 7));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-400, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/stars2.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 8 && i < 10) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 6));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-500, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/rotaryStar2.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 10 && i < 12) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 6));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/blueStar.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        }
    }
}
