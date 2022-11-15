/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Game
*/

#include "Game.hpp"

rtp::Game::Game(rtp::scene_package_t pack, std::vector<int> &startGamePayload): AScene(pack), _startGamePayload(startGamePayload)
{
    _enemyTimer = 2;
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
    for (int i = 1; i < _startGamePayload.size(); i += 2) {
        if (_startGamePayload[i] == _playerId)
            _playerSystem.addPlayer(_reg, _texture, _playerId, _startGamePayload[i + 1]);
    }
    std::cout << "Player id " << _playerId << std::endl;
    if (_level == 5) _enemySystem._addBoss(_reg, _texture);
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
    _reg.registerComponents(eng::SparseArray<rtp::Canon>());
    _reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    _reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    _reg.registerComponents(eng::SparseArray<rtp::Synced>());
}

void rtp::Game::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape")) {
        _sceneEvent = 2;
        _sceneNumber = 2;
    }
    _clientSystems.receiveData(_reg, _texture);
    //Controls
    if (_graphic.isWindowFocused())
        _playerSystem.control(_reg, _input);
    _playerSystem.controlMovement(_reg, _graphic.getDeltaSeconds());
    _clientSystems.sendInputData(_reg);
    _physic.applyGravity(_reg);

    _physic.applyVelocities(_reg);
    _playerSystem.limitPlayer(_reg);
    // Shooting
    _playerSystem.controlFireSystem(_reg, _graphic.getDeltaSeconds());
    _playerSystem.shootSystem(_reg);

    // Backgrounds
    _backgroundSystem.loop(_reg);

    _killSystem.killOutOfBounds(_reg);
    _killSystem.killBullets(_reg);
    _killSystem.killDeadEnemies(_reg, _score, _textSystem, _graphic.getDeltaSeconds(), _texture);
    _killSystem.killDeadPlayers(_reg);
    // Victory / defeat
    if (_killSystem.allPlayerKilled(_reg)) {
        _sceneEvent = 2;
        _sceneNumber = 7;
    }
    if ((_level >= 1 && _level <= 4 && _score >= _level * 100) || _level == 5 && _score >= 10000) {
        _sceneEvent = 2;
        _sceneNumber = 6;
    }
    // Play sounds & music
    _audio.playMusic(_reg);
    _audio.playSound(_reg);
    // Enemy
    _enemySystem.playerBullets(_reg);
    _enemySystem.enemyCollision(_reg, _physic);
    if (_level == 5)
        _enemySystem.bossAnimation(_reg);
    _enemySystem.spawnEnemies(_reg, _enemyTimer, _level, _graphic.getDeltaSeconds(), _texture);
    // clear, draw & display
    _graphic.clear();
    _graphic.animateSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.particleSystem(_reg);
    _graphic.writeSystem(_reg);
    _graphic.display();
}

void rtp::Game::_addMusic()
{
    eng::Entity music = _reg.spawnEntity();

    _reg.addComponent<eng::Music>(music, eng::Music("assets/music.ogg", true));
}

void rtp::Game::_addScore()
{
    eng::Entity score = _reg.spawnEntity();

    _reg.addComponent<eng::Position>(score, eng::Position(850, 0, 0));
    _reg.addComponent<eng::Writable>(score, eng::Writable("score", "SCORE : 0", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::Game::_addBackgrounds()
{
    for (int i = 0; i < 10; i++) {
        eng::Entity bg = _reg.spawnEntity();
        if (i >= 0 && i < 2) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 10));
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
        }
    }
}
