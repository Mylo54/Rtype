/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ChooseLvl
*/

#include "ChooseLvl.hpp"

rtp::ChooseLvl::ChooseLvl(rtp::scene_package_t pack): AScene(pack)
{
}   

rtp::ChooseLvl::~ChooseLvl()
{
}

void rtp::ChooseLvl::setupScene()
{
    setupRegistry();
    _addBackgrounds();
    _addButtons();
    _tcpClient.connect(_host, "4000");
    _udpClient.connect(_host, "4000");
    std::vector<int> vec = {502};
    _udpClient.send(vec);
    // _addEarth();
}

void rtp::ChooseLvl::setupRegistry()
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

void rtp::ChooseLvl::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _sceneEvent = 1;

    // Animate buttons
    _buttonSystem.buttonStateSystem(_reg, _input);
    // Apply button actions
    _buttonSystem.buttonClick(_reg, _input);

    // Backgrounds
    _backgroundSystem.loop(_reg);

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

void rtp::ChooseLvl::_addButtons()
{
    _addButtonLvl1();
    _addButtonLvl2();
    _addButtonLvl3();
    _addButtonLvl4();
    _addButtonLvlFinal();
}

void rtp::ChooseLvl::_addBackgrounds()
{
    eng::Entity bg1 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg1, eng::Position(0, 0, 10));
    _reg.addComponent<eng::Drawable>(bg1, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
    eng::Entity bg2 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg2, eng::Position(0, 0, 9));
    _reg.addComponent<eng::Drawable>(bg2, eng::Drawable(_texture.getTextureFromFile("assets/fog1.png")));
    eng::Entity bg3 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg3, eng::Position(0, 0, 8));
    _reg.addComponent<eng::Drawable>(bg3, eng::Drawable(_texture.getTextureFromFile("assets/stars1.png")));
    eng::Entity bg4 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg4, eng::Position(0, 0, 7));
    _reg.addComponent<eng::Drawable>(bg4, eng::Drawable(_texture.getTextureFromFile("assets/stars2.png")));
    eng::Entity bg5 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg5, eng::Position(0, 0, 6));
    _reg.addComponent<eng::Drawable>(bg5, eng::Drawable(_texture.getTextureFromFile("assets/rotaryStar2.png")));
}

void rtp::ChooseLvl::_addButtonLvl1()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl1 = std::bind(&ChooseLvl::_btnFctlvl1, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 200, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl1, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 1", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 200, 0));
}

void rtp::ChooseLvl::_addButtonLvl2()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl = std::bind(&ChooseLvl::_btnFctlvl2, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 300, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 2", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 300, 0));
}

void rtp::ChooseLvl::_addButtonLvl3()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl = std::bind(&ChooseLvl::_btnFctlvl3, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 400, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 3", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 400, 0));
}

void rtp::ChooseLvl::_addButtonLvl4()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl = std::bind(&ChooseLvl::_btnFctlvl4, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 4", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));
}

void rtp::ChooseLvl::_addButtonLvlFinal()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;

    std::function<int()> lvl = std::bind(&ChooseLvl::_btnFctlvlB, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level Final", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));
}

int rtp::ChooseLvl::_btnFctlvl1()
{
    _sceneEvent = 2;
    _sceneNumber = 0;
    _level = 1;
    return (0);
}

int rtp::ChooseLvl::_btnFctlvl2()
{
    // TODO: Modify destination to ??, menu
    _sceneEvent = 2;
    _sceneNumber = 0;
    _level = 2;
    return (0);
}

int rtp::ChooseLvl::_btnFctlvl3()
{
    // TODO: Modify destination to ??, menu
    _sceneEvent = 2;
    _sceneNumber = 0;
    _level = 3;
    return (0);
}

int rtp::ChooseLvl::_btnFctlvl4()
{
    // TODO: Modify destination to ??, menu
    _sceneEvent = 2;
    _sceneNumber = 0;
    _level = 4;
    return (0);
}

int rtp::ChooseLvl::_btnFctlvlB()
{
    // TODO: Modify destination to ??, menu
    _sceneEvent = 2;
    _sceneNumber = 0;
    _level = 5;
    return (0);
}