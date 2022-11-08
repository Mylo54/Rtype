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

int rtp::Client::run()
{
    _sceneEvent = sceneEvent::none;
    _sceneNumber = sceneNumber::menu;
    _registries.addRegistry("start");

    std::cout << "Client is up!" << std::endl;
    while (_graphics.isWindowOpen()) {
        // this will be replaced by scenes.top().run;
        {
            _graphics.eventCatchWindow();
            _graphics.clear();
            _graphics.display();
        }

        // change scene & registry when event;
        if (_sceneEvent != rtp::sceneEvent::none) {
            _registries.addRegistry("new");
            //scenes.push(askedscene);
        }
    }
    return (0);
}
