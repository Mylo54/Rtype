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
#include <string.h>
#include <cstring>
#include <string>
#include <sstream>
#include <array>

std::string logPath = "";
extern std::string logPath;

void newLogPath(void)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    logPath = std::to_string(ltm->tm_mday) + "-" +
    std::to_string(1 + ltm->tm_mon) + "-" + std::to_string(1900 + ltm->tm_year)
    + "_" + std::to_string(5 + ltm->tm_hour) + "h"
    + std::to_string(ltm->tm_min) + "m" + std::to_string(ltm->tm_sec)
    + "s.log";
    std::ofstream out(logPath.c_str());
    out << "Log from this run:\n";
    out.close();
}

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

void setRegistry(eng::RegistryManager &m, std::string name)
{
    eng::Registry &reg = m.getTop();
    eng::SparseArray<rtp::Position> position;
    eng::SparseArray<rtp::Velocity> velocity;
    eng::SparseArray<rtp::Drawable> drawable;
    eng::SparseArray<rtp::Controllable> control;
    eng::SparseArray<rtp::Shooter> shooter;
    eng::SparseArray<rtp::Background> backgrounds;
    eng::SparseArray<rtp::AudioSource> sounds;

    reg.setName(name);
    reg.setDebugMode(m.getDebugMode());
    reg.setLogPath(m.getLogPath());
    reg.registerComponents(position);
    reg.registerComponents(velocity);
    reg.registerComponents(drawable);
    reg.registerComponents(control);
    reg.registerComponents(shooter);
    reg.registerComponents(backgrounds);
    reg.registerComponents(sounds);
}

int main(int argc, char **argv)
{
    eng::RegistryManager manage;
    sf::Clock c;
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");
    rtp::Systems systems(w, c);
    eng::Log log;

    manage.getRegistries().push(eng::Registry());
    setRegistry(manage, "r1");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            manage.setDebugMode(true);
            manage.setLogPath(log.createPath());
        }
    eng::Registry &r = manage.getTop();
    std::vector<eng::Entity> bgs = makeBackgrounds(r, w, c);
    eng::Entity baba = r.spawnEntity();
    w.setFramerateLimit(60);

    r.addComponent<rtp::Position>(baba, rtp::Position(0, 0, 0));
    r.addComponent<rtp::Velocity>(baba, rtp::Velocity(0, 0));
    r.addComponent<rtp::Shooter>(baba, rtp::Shooter("../assets/bullet.png", 25.0, std::vector<float>({65, 25, 0})));
    r.addComponent<rtp::Drawable>(baba, rtp::Drawable("../assets/platypus_spaceship.png", w, c, 1, sf::IntRect(0, 0, 65, 49), 0.005));
    r.addComponent<rtp::Controllable>(baba, rtp::Controllable(w));

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
        //systems.sendData(r);
        systems.clearSystem(r);
        systems.backgroundSystem(r);
        systems.drawSystem(r);
        systems.playSoundSystem(r);
        systems.displaySystem(r);
    }
    return 0;
}