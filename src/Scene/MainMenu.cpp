/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

rtp::MainMenu::MainMenu(rtp::scene_package_t pack): AScene(pack)
{
}

rtp::MainMenu::~MainMenu()
{
}

void rtp::MainMenu::setupScene()
{
    setupRegistry();
    _addBackgrounds();
    _addButtons();
    _addEarth();
}

void rtp::MainMenu::setupRegistry()
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

void rtp::MainMenu::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _graphic.closeWindow();
    if (_input.isActionJustPressed("ui_left")) {
        _sceneEvent = 2;
        _sceneNumber = 8;
    }
        
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

void rtp::MainMenu::_addButtons()
{
    _addSinglePlayerButton();
    _addButtonExit();
    _addButtonMultiplayer();
    _addButtonSettings();
    _addButtonCredits();
}

void rtp::MainMenu::_addSinglePlayerButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int()> chooseLvl = std::bind(&MainMenu::_chooseLvlBtnFunction, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(chooseLvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Singleplayer", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));
}

void rtp::MainMenu::_addButtonExit()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> exit = std::bind(&MainMenu::_exitBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Exit", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 700, 0));
}

void rtp::MainMenu::_addButtonMultiplayer()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;    

    std::function<int()> multi = std::bind(&MainMenu::_multiBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(multi, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Multiplayer", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));
}

void rtp::MainMenu::_addButtonSettings()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> settings = std::bind(&MainMenu::_settingBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(970, 700, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(settings, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(990, 700, 0));
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Options", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::MainMenu::_addButtonCredits()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> credits = std::bind(&MainMenu::_creditsBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(1632, 891, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(credits, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(1697, 894, 0));
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Credits", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::MainMenu::_addBackgrounds()
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
    eng::Entity title = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(title, eng::Position(0, 0, 5));
    _reg.addComponent<eng::Drawable>(title, eng::Drawable(_texture.getTextureFromFile("assets/PM_bckgrd.png")));
}

void rtp::MainMenu::_addEarth()
{
    eng::Entity bg = _reg.spawnEntity();
    _reg.addComponent<eng::Velocity>(bg, eng::Velocity(0, 0, 35));

    _reg.addComponent<eng::Position>(bg, eng::Position(1920 / 2, 1300, 0));
    _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/terre.png")));
    _reg.getComponents<eng::Drawable>()[bg.getId()].value().sprite.setScale(2, 2);
    auto &draw = _reg.getComponents<eng::Drawable>();
    int x = draw[bg.getId()].value().sprite.getTexture()->getSize().x / 2;
    int y = draw[bg.getId()].value().sprite.getTexture()->getSize().y / 2;
    draw[bg.getId()].value().sprite.setOrigin(x, y);
    draw[bg.getId()].value().protect = true;
}

int rtp::MainMenu::_exitBtnFunction()
{
    _graphic.closeWindow();
    return (0);
}

int rtp::MainMenu::_chooseLvlBtnFunction()
{
    // TODO: Modify destination to Choose level menu
    _sceneEvent = 2;
    _sceneNumber = 4;
    return (0);
}

int rtp::MainMenu::_multiBtnFunction()
{
    // TODO: Modify destination to ??, menu
    _sceneEvent = 2;
    _sceneNumber = 5;
    return (0);
}

int rtp::MainMenu::_settingBtnFunction()
{
    // TODO: Modify destination to Choose level menu
    _sceneEvent = 2;
    _sceneNumber = 3;
    return (0);
}

int rtp::MainMenu::_creditsBtnFunction()
{
    // TODO: Modify destination to Choose level menu
    _sceneEvent = 2;
    _sceneNumber = 8;
    return (0);
}
