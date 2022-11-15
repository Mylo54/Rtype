/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** WaitingRoom
*/

#include "WaitingRoom.hpp"

rtp::WaitingRoom::WaitingRoom(rtp::scene_package_t pack, std::vector<int> &startGamePayload): AScene(pack), _startGamePayload(startGamePayload)
{
}

rtp::WaitingRoom::~WaitingRoom()
{
}

void rtp::WaitingRoom::setupScene()
{
    _tcpClient.connect(_host, "4000");
    _udpClient.connect(_host, "4000");
    std::vector<int> vec = {501};
    _udpClient.send(vec);
    setupRegistry();
    _addBackgrounds();
    _addButtonStart();
}

void rtp::WaitingRoom::setupRegistry()
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

void rtp::WaitingRoom::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape")) {
        _sceneEvent = 1;
    }
    // Animate buttons
    _buttonSystem.buttonStateSystem(_reg, _input);
    // Apply button actions
    _buttonSystem.buttonClick(_reg, _input);

    _physic.applyVelocities(_reg);

    // Backgrounds
    _backgroundSystem.loop(_reg);

    // Play sounds & music
    _audio.playMusic(_reg);
    _audio.playSound(_reg);

    // clear, draw & display
    _graphic.clear();
    _graphic.animateSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.writeSystem(_reg);
    _graphic.particleSystem(_reg);
    _graphic.display();
    std::vector<int> vec = {504};
    _udpClient.send(vec);
    std::vector<int> res = _udpClient.receive();
    if (res[0] == 401)
        _playerId = res[1];
    if (res[0] == 403) {
        _level = 5;
        _sceneEvent = 2;
        _sceneNumber = 0;
        _startGamePayload = res;
    }
    while (_nbrPlayer > _nbrPlayerDraw)
        addPlayer(_nbrPlayerDraw + 1, 0);
    if (res[0] == 404)
        _nbrPlayer = res[1];
}

void rtp::WaitingRoom::_addBackgrounds()
{
    for (int i = 0; i < 10; i++) {
        eng::Entity bg = _reg.spawnEntity();
        if (i >= 0 && i < 2) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 10));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 2 && i < 4) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 9));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/fog1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        } if (i >= 4 && i < 6) {
            _reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 8));
            _reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
            _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/stars1.png")));
            _reg.addComponent<rtp::Background>(bg, rtp::Background());
        }
    }
}

void rtp::WaitingRoom::_addButtonStart()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl = std::bind(&WaitingRoom::_btnFctStart, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "GO", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(723, 500, 0));
}

int rtp::WaitingRoom::_btnFctStart()
{
    _level = 5;
    _sceneEvent = 2;
    _sceneNumber = 0;
    std::vector<int> vec = {502};
    _udpClient.send(vec);
    return (0);
}

eng::Entity rtp::WaitingRoom::addPlayer(int playerId, int syncId)
{
    eng::Entity player = _reg.spawnEntity();

    _reg.addComponent<eng::Position>(player, eng::Position(350, 180 * (playerId), 0));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    _reg.addComponent<eng::Drawable>(player, eng::Drawable("assets/players.png", 1, rect, 0.10));
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
    _nbrPlayerDraw += 1;
    return player;
}
