/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** Pause
*/

#include "Pause.hpp"

rtp::Pause::Pause(rtp::scene_package_t pack): AScene(pack)
{
}

rtp::Pause::~Pause()
{
}

void rtp::Pause::setupScene()
{
    setupRegistry();
    _addButtons();
    _addBackgrounds();
}

void rtp::Pause::setupRegistry()
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
    _reg.registerComponents(eng::SparseArray<rtp::Button>());
}

void rtp::Pause::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _sceneEvent = 1;

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

void rtp::Pause::_addButtons()
{
    _addResumeButton();
    _addSettingsButton();
    _addMainMenuButton();
}

void rtp::Pause::_addBackgrounds()
{
    eng::Entity bg = _reg.spawnEntity();

    _reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/PM_bckgrd.png")));
}

void rtp::Pause::_addResumeButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntext = _reg.spawnEntity();
    int scale = 4;
    std::function<int()> resume = std::bind(&Pause::_resumeBtn, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(832, 442, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(resume, 0, 0, 128 * 2, 32 * 1.5));
    _reg.emplaceComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    _reg.addComponent<eng::Writable>(btntext, eng::Writable("Button", "RESUME", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntext, eng::Position(897, 445, 0));
}

void rtp::Pause::_addSettingsButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntext = _reg.spawnEntity();
    int scale = 4;
    std::function<int()> settings = std::bind(&Pause::_settingsBtn, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(832, 491, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(settings, 0, 0, 128 * 2, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    _reg.addComponent<eng::Writable>(btntext, eng::Writable("Button", "OPTIONS", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntext, eng::Position(897, 494, 0));
}

void rtp::Pause::_addMainMenuButton()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntext = _reg.spawnEntity();
    int scale = 4;
    std::function<int()> mainMenu = std::bind(&Pause::_mainMenuBtn, this);

    _reg.addComponent<eng::Position>(btn, eng::Position(832, 540, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(mainMenu, 0, 0, 128 * 2, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    _reg.addComponent<eng::Writable>(btntext, eng::Writable("Button", "MAIN MENU", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntext, eng::Position(880, 543, 0));
}

int rtp::Pause::_resumeBtn()
{
    _sceneEvent = 1;
    return (0);
}

int rtp::Pause::_settingsBtn()
{
    _sceneEvent = 2;
    _sceneNumber = 3;
    return (0);
}

int rtp::Pause::_mainMenuBtn()
{
    _sceneEvent = 2;
    _sceneNumber = 1;
    return (0);
}
