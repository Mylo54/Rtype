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
}

void rtp::Game::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _sceneEvent = 2;
        _sceneNumber = 2;
    // Animate buttons
    _buttonSystem.buttonStateSystem(_reg, _input);
    // Apply button actions
    _buttonSystem.buttonClick(_reg, _input);

    _physic.applyVelocities(_reg);

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

    _reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    _reg.addComponent<eng::Velocity>(player, eng::Velocity());
    // reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    _reg.addComponent<eng::Drawable>(player, eng::Drawable(_texture.getTextureFromFile("assets/players.png"), 1, rect, 0.10));
    // reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    // reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    // reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    _reg.addComponent<eng::RectCollider>(player, eng::RectCollider(40, 16));
    _reg.addComponent<eng::RigidBody>(player, eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));
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
    for (int i = 0; i < 6; i++) {
        eng::Entity bg = _reg.spawnEntity();
        _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 0));
        if (i < 2) {
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-400, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/foreground.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } else if (i < 4) {
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/middleground.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } else {
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        }
    }
}
