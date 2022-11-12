/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Credits
*/

#include "Credits.hpp"

rtp::Credits::Credits(rtp::scene_package_t pack): AScene(pack)
{
}

rtp::Credits::~Credits()
{
}

void rtp::Credits::setupScene()
{
    setupRegistry();
    _addBackgrounds();
    _addTitle();
    _addTeamText();
    _addButtons();
}

void rtp::Credits::setupRegistry()
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

void rtp::Credits::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape")) {
        _sceneEvent = 2;
        _sceneNumber = 1;
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
    // _graphic.animateSystem(_reg);
    _graphic.particleSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.writeSystem(_reg);
    _graphic.display();
}

void rtp::Credits::_addTitle()
{
    eng::Entity text = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(text, eng::Writable("Title", "Thanks for playing", "assets/MetroidPrimeHunters.ttf", 150, sf::Color::Blue));
    _reg.addComponent<eng::Position>(text, eng::Position(270, 50, 0));
}

void rtp::Credits::_addTeamText()
{
    eng::Entity head = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(head, eng::Writable("Team", "The SuperTeam :", "assets/MetroidPrimeHunters.ttf", 80, sf::Color::White, sf::Text::Style::Underlined));
    _reg.addComponent<eng::Position>(head, eng::Position(650, 300, 0));

    eng::Entity clovis = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(clovis, eng::Writable("Clovis", "Clovis  \"Refactorizer\"  Schneider", "assets/MetroidPrimeHunters.ttf", 40, sf::Color::White));
    _reg.addComponent<eng::Position>(clovis, eng::Position(650, 450, 0));

    eng::Entity chloe = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(chloe, eng::Writable("Chloe", "Chloe  \"No gouter\"  Lere", "assets/MetroidPrimeHunters.ttf", 40, sf::Color::White));
    _reg.addComponent<eng::Position>(chloe, eng::Position(650, 500, 0));

    eng::Entity damien = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(damien, eng::Writable("Damien", "Damien  \"Krabu\"  Demontis", "assets/MetroidPrimeHunters.ttf", 40, sf::Color::White));
    _reg.addComponent<eng::Position>(damien, eng::Position(650, 550, 0));

    eng::Entity mylo = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(mylo, eng::Writable("Mylo", "Mylo  \"The librarian\"  Jeandat", "assets/MetroidPrimeHunters.ttf", 40, sf::Color::White));
    _reg.addComponent<eng::Position>(mylo, eng::Position(650, 600, 0));

    eng::Entity vivant = _reg.spawnEntity();
    _reg.addComponent<eng::Writable>(vivant, eng::Writable("Vivant", "Vivant  \"Zen\"  Garrigues", "assets/MetroidPrimeHunters.ttf", 40, sf::Color::White));
    _reg.addComponent<eng::Position>(vivant, eng::Position(650, 650, 0));
}

void rtp::Credits::_addButtons()
{
    _addButtonMainMenu();
}

void rtp::Credits::_addBackgrounds()
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

void rtp::Credits::_addButtonMainMenu()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> menu = std::bind(&Credits::_mainMenuBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(1632, 891, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(menu, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Main Menu", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(1697, 894, 0));
}

int rtp::Credits::_mainMenuBtnFunction()
{
    _sceneEvent = 2;
    _sceneNumber = 1;
    return 0;
}
