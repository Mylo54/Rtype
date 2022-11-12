/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(): _graphics(1920, 1080, "Super R-Type"),
_inputs(_graphics.getRenderWindow()), _physics(_graphics.getDeltaSeconds()),
_sceneManager(_registries)
{
    std::cout << "Client has been created" << std::endl;
    _graphics.setFrameRateLimit(60);
}

rtp::Client::~Client()
{
    //TODO: clear scene stack
}

rtp::scene_package_t rtp::Client::_makePackage()
{
    scene_package_t pkg = {_registries.getTop(), _graphics, _physics, _audio,
        _inputs, _textures, _sceneEvent, _sceneNumber};

    return (pkg);
}

void rtp::Client::_setupInputEvents()
{
    _inputs.addAction("ui_up");
    _inputs.addAction("ui_down");
    _inputs.addAction("ui_left");
    _inputs.addAction("ui_right");
    _inputs.addAction("ui_accept");
    _inputs.addAction("ui_escape");
    _inputs.addAction("ui_click");
    _inputs.addAction("ui_pause");
    _inputs.addAction("ui_fire");

    _inputs.addEvent("ui_up", eng::SuperInput::Key::up);
    _inputs.addEvent("ui_down", eng::SuperInput::Key::down);
    _inputs.addEvent("ui_left", eng::SuperInput::Key::left);
    _inputs.addEvent("ui_right", eng::SuperInput::Key::right);
    _inputs.addEvent("ui_up", eng::SuperInput::Key::z);
    _inputs.addEvent("ui_down", eng::SuperInput::Key::s);
    _inputs.addEvent("ui_left", eng::SuperInput::Key::q);
    _inputs.addEvent("ui_right", eng::SuperInput::Key::d);
    _inputs.addEvent("ui_accept", eng::SuperInput::Key::enter);
    _inputs.addEvent("ui_escape", eng::SuperInput::Key::escape);
    _inputs.addEvent("ui_pause", eng::SuperInput::Key::escape);
    _inputs.addEvent("ui_pause", eng::SuperInput::Key::p);
    _inputs.addEvent("ui_fire", eng::SuperInput::Key::space);
    _inputs.addEvent("ui_pause", eng::SuperInput::JoyButton::start, 0);
    _inputs.addEvent("ui_click", eng::SuperInput::MouseButton::left);

    _inputs.addEvent("ui_up", eng::SuperInput::JoyAnalog::leftStickX, 0);
    _inputs.addEvent("ui_left", eng::SuperInput::JoyAnalog::leftStickY, 0);
    _inputs.addEvent("ui_accept", eng::SuperInput::JoyButton::a, 0);
}

// This will end in a SceneManager Object in the engine after the end of the
// refactor thinking, no worries ^^
void rtp::Client::_handleSceneEvents()
{
    if (_sceneEvent == rtp::sceneEvent::pushScene) {
        _registries.addRegistry("new");
        if (_sceneNumber == rtp::sceneNumber::option) {
            _scenes.push(new rtp::Settings(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::chooseLvl) {
            _scenes.push(new rtp::ChooseLvl(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::game) {
            _scenes.push(new rtp::Game(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::menu) {
            _scenes.push(new rtp::MainMenu(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::pause) {
            _scenes.push(new rtp::Pause(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::waiting) {
            _scenes.push(new rtp::WaitingRoom(_makePackage()));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::win) {
            _scenes.push(new rtp::End(_makePackage(), true));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::loose) {
            _scenes.push(new rtp::End(_makePackage(), false));
            _scenes.top()->setupScene();
        }
        if (_sceneNumber == rtp::sceneNumber::credits) {
            _scenes.push(new rtp::Credits(_makePackage()));
            _scenes.top()->setupScene();
        }
    }
    if (_sceneEvent == rtp::sceneEvent::popScene) {
        _registries.popRegistry();
        delete _scenes.top();
        _scenes.pop();
    }
    _sceneEvent = rtp::sceneEvent::none;
}

int rtp::Client::run()
{
    _setupInputEvents();
    _registries.addRegistry("start");
    rtp::Settings *optionScene = new rtp::Settings(_makePackage());
    rtp::MainMenu *mainMenuScene = new rtp::MainMenu(_makePackage());
    rtp::ChooseLvl *chooseLvl = new rtp::ChooseLvl(_makePackage());
    rtp::Game *game = new rtp::Game(_makePackage());
    // _scenes.push(optionScene);
    // _scenes.push(mainMenuScene);
    _scenes.push(mainMenuScene);

    std::cout << "Client is up!" << std::endl;
    _scenes.top()->setupScene();
    // _scenes.top()->setupRegistry();
    while (_graphics.isWindowOpen() && !_scenes.empty()) {
        // run systems
        _scenes.top()->systemRun();
        // change scene & registry if asked
        _handleSceneEvents();
    }
    return (0);
}
