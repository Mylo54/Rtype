/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "iostream"
#include "../Components/Components.hpp"
#include "../Systems/Systems.hpp"
#include "../Engine/Registry.hpp"
#include "../Engine/RegistryManager.hpp"
#include "../Engine/Log.hpp"
#include <string.h>

eng::Registry createRegistry(bool isDebugMode, std::string name)
{
    eng::Registry res;
    res.setName(name);
    eng::SparseArray<rtp::Position> position;
    eng::SparseArray<rtp::Velocity> velocity;
    eng::SparseArray<rtp::Drawable> drawable;
    eng::SparseArray<rtp::Controllable> control;

    if (isDebugMode) res.setDebugMode(true);
    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    res.registerComponents(control);
    return (res);
}

int main(int argc, char **argv)
{
    sf::Clock c;
    rtp::Systems systems;
    eng::RegistryManager engine;
    eng::Registry reg = createRegistry(true, "Registry7");
    eng::Log log;

    engine.setDebugMode(false);
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            engine.setDebugMode(true);
            engine.setLogPath(log.createPath());
        }
    engine.addRegistry(reg);
    eng::Entity baba = engine.getRegistries().top().spawnEntity();

    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");
    w.setFramerateLimit(60);
    engine.getRegistries().top().addComponent<rtp::Position>(baba, rtp::Position(0, 0, 0));
    engine.getRegistries().top().addComponent<rtp::Velocity>(baba, rtp::Velocity(0, 0));
    engine.getRegistries().top().addComponent<rtp::Drawable>(baba, rtp::Drawable("../assets/platypus_spaceship.png", w, c, 1, sf::IntRect(0, 0, 65, 49), 0.005));
    engine.getRegistries().top().addComponent<rtp::Controllable>(baba, rtp::Controllable(w));

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        systems.controlSystem(engine.getRegistries().top());
        systems.positionSystem(engine.getRegistries().top());
        systems.drawSystem(engine.getRegistries().top());
    }
    return 0;
}