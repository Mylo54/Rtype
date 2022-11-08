/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(): _graphics(1920, 1080, "Super R-Type"),
_inputs(_graphics.getRenderWindow()), _physics(_graphics.getDeltaSeconds())
{
    std::cout << "Client has been created" << std::endl;
}

rtp::Client::~Client()
{
}

rtp::scene_package_t rtp::Client::_makePackage()
{
    scene_package_t pkg = {_registries.getTop(), _graphics, _physics, _audio,
        _net, _inputs, _textures};

    return (pkg);
}

int rtp::Client::run()
{
    _sceneEvent = sceneEvent::none;
    _sceneNumber = sceneNumber::menu;
    _registries.addRegistry("start");
    rtp::AScene defaultScene(_makePackage());
    _scenes.push(&defaultScene);

    std::cout << "Client is up!" << std::endl;
    defaultScene.setupRegistry();
    while (_graphics.isWindowOpen() && !_scenes.empty()) {
        _scenes.top()->systemRun();

        // change scene & registry when event asks for;
        if (_sceneEvent == rtp::sceneEvent::pushScene) {
            _registries.addRegistry("new");
            //scenes.push(askedscene);
        }
        if (_sceneEvent == rtp::sceneEvent::popScene) {
            _registries.popRegistry();
            _scenes.pop();
        }
    }
    return (0);
}
