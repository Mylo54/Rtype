/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** End
*/

#include "End.hpp"

rtp::End::End(rtp::scene_package_t pack, bool win): AScene(pack), _win(win)
{
}

rtp::End::~End()
{
}

void rtp::End::setupScene()
{
    setupRegistry();
    _addResult();
    _addButtons();
    _addBackgrounds();
}

void rtp::End::setupRegistry()
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

void rtp::End::systemRun()
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

void rtp::End::_addResult()
{
    eng::Entity text = _reg.spawnEntity();
    std::string result = _win ? "You win !" : "You lose";
    sf::Color color = _win ? sf::Color::Green : sf::Color::Red;
    sf::Text::Style style = _win ? sf::Text::Style::Italic : sf::Text::Style::Underlined;

    _reg.addComponent<eng::Writable>(text, eng::Writable("Result", result, "assets/MetroidPrimeHunters.ttf", 200, color, style));
    _reg.addComponent<eng::Position>(text, eng::Position(600, 150, 0));
}

void rtp::End::_addButtons()
{
    _addButtonMainMenu();
    _addButtonRestart();
    _addButtonExit();
}

void rtp::End::_addBackgrounds()
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
}

void rtp::End::_addButtonMainMenu()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> menu = std::bind(&End::_mainMenuBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(832, 491, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(menu, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Main Menu", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(897, 494, 0));
}

void rtp::End::_addButtonRestart()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> restart = std::bind(&End::_restartBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(832, 442, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(restart, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Restart", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(897, 445, 0));
}

void rtp::End::_addButtonExit()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int()> exit = std::bind(&End::_exitBtnFunction, this);
    _reg.addComponent<eng::Position>(btn, eng::Position(832, 540, 0));
    _reg.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Exit", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(897, 543, 0));
}

int rtp::End::_mainMenuBtnFunction()
{
    _sceneEvent = 2;
    _sceneNumber = 1;
    return 0;
}

int rtp::End::_restartBtnFunction()
{
    _sceneEvent = 2;
    _sceneNumber = 4;
    return 0;
}

int rtp::End::_exitBtnFunction()
{
    _graphic.closeWindow();
    return (0);
}