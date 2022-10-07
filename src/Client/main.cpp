/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "iostream"
#include "../Components/Components.hpp"
#include "../ClientSystems/Systems.hpp"
#include "../Engine/Registry.hpp"
#include "../Engine/IRegistry.hpp"
#include "../Engine/RegistryManager.hpp"
#include <string.h>
#include <cstring>
#include <string>
#include <sstream>
#include <array>
#include "Client.hpp"

std::vector<eng::Entity> makeBackgrounds(eng::Registry &reg, sf::RenderWindow &w, sf::Clock &c)
{
    eng::Entity fg1 = reg.spawnEntity();
    eng::Entity fg2 = reg.spawnEntity();
    eng::Entity mg1 = reg.spawnEntity();
    eng::Entity mg2 = reg.spawnEntity();
    eng::Entity bg1 = reg.spawnEntity();
    eng::Entity bg2 = reg.spawnEntity();
    std::vector<eng::Entity> bgs = {fg1, fg2, mg1, mg2, bg1, bg2};

    // Foregrounds
    reg.addComponent<rtp::Position>(fg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(fg1, rtp::Velocity(-20, 0));
    reg.addComponent<rtp::Background>(fg1, rtp::Background("../assets/foreground.png"));
    reg.addComponent<rtp::Position>(fg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(fg2, rtp::Velocity(-20, 0));
    reg.addComponent<rtp::Background>(fg2, rtp::Background("../assets/foreground.png"));

    // Middlegrounds
    reg.addComponent<rtp::Position>(mg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(mg1, rtp::Velocity(-10, 0));
    reg.addComponent<rtp::Background>(mg1, rtp::Background("../assets/middleground.png"));
    reg.addComponent<rtp::Position>(mg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(mg2, rtp::Velocity(-10, 0));
    reg.addComponent<rtp::Background>(mg2, rtp::Background("../assets/middleground.png"));
    
    // Backgrounds
    reg.addComponent<rtp::Position>(bg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(bg1, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Background>(bg1, rtp::Background("../assets/background.png"));
    reg.addComponent<rtp::Position>(bg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(bg2, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Background>(bg2, rtp::Background("../assets/background.png"));
    return bgs;
}

void setRegistry(eng::RegistryManager &m)
{
    eng::Registry &reg = m.getTop();

    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::AudioSource>());
}

eng::Entity makePlayer(eng::Registry &r, sf::RenderWindow &w, sf::Clock &c)
{
    eng::Entity baba = r.spawnEntity();

    r.addComponent<rtp::Position>(baba, rtp::Position(200, 540, 0));
    r.addComponent<rtp::Velocity>(baba, rtp::Velocity(0, 0));
    r.addComponent<rtp::Shooter>(baba, rtp::Shooter("../assets/bullet.png", 25.0, 4, std::vector<float>({65, 25, 0})));
    r.addComponent<rtp::Drawable>(baba, rtp::Drawable("../assets/platypus_spaceship.png", w, c, 1, sf::IntRect(0, 0, 65, 49), 0.005));
    r.addComponent<rtp::Controllable>(baba, rtp::Controllable(w));

    return baba;
}

eng::Entity makeEnemy(eng::Registry &r, sf::RenderWindow &w, sf::Clock &c)
{
    eng::Entity res = r.spawnEntity();

    r.addComponent<rtp::Position>(res, rtp::Position(1920, rand() % 1080, 0));
    r.addComponent<rtp::Velocity>(res, rtp::Velocity(-5, 0));
    r.addComponent<rtp::Drawable>(res, rtp::Drawable("../assets/flyers.png", w, c, 3, sf::IntRect(0, 0, 40, 16), 0.005));

    r.getComponents<rtp::Drawable>()[res.getId()].value().sprite.setScale(2, 2);
    return res;
}

int main(int argc, char **argv)
{
    rtp::Client client(3232);
    client.run();
    eng::RegistryManager manage;
    sf::Clock c;
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");
    rtp::Systems systems(w, c);
    eng::Log log;
    // eng::IRegistry ireg;
    srand(time(0));

    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            manage.setDebugMode(true);
            manage.createLogPath();
        }
    manage.addRegistry("r1");
    setRegistry(manage);
    manage.addRegistry("r1");
    setRegistry(manage);
    eng::Registry &r = manage.getTop();
    std::vector<eng::Entity> bgs = makeBackgrounds(r, w, c);
    w.setFramerateLimit(60);

    eng::Entity baba = makePlayer(r, w, c);
    eng::Entity enemy = makeEnemy(r, w, c);
    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        //systems.receiveData(r);
        systems.controlSystem(r);
        systems.controlMovementSystem(r);
        systems.controlFireSystem(r);
        systems.positionSystem(r);
        systems.shootSystem(r);
        systems.animateSystem(r);
        //systems.sendData(r);
        systems.clearSystem(r);
        systems.backgroundSystem(r);
        systems.drawSystem(r);
        systems.playSoundSystem(r);
        systems.displaySystem(r);
    }
    return 0;
}