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
#include <cstring>
#include <string>
#include <sstream>
#include <array>

std::string logPath = "";
extern std::string logPath;

eng::Registry createRegistry(bool isDebugMode, std::string name)
{
    eng::Registry res;
    res.setName(name);
    eng::SparseArray<rtp::Position> position;
    eng::SparseArray<rtp::Velocity> velocity;
    eng::SparseArray<rtp::Drawable> drawable;
    eng::SparseArray<rtp::Controllable> control;
    eng::SparseArray<rtp::Shooter> shooter;
    eng::SparseArray<rtp::Background> backgrounds;
    eng::SparseArray<rtp::AudioSource> sounds;

    if (isDebugMode) res.setDebugMode(true);
    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    res.registerComponents(control);
    res.registerComponents(shooter);
    res.registerComponents(backgrounds);
    res.registerComponents(sounds);
    return (res);
}

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

int main(int argc, char **argv)
{
    eng::Registry reg;
    sf::Clock c;
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");
    rtp::Systems systems(w, c);

    reg.setName("Registry1");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            reg.setDebugMode(true);
            newLogPath();
        }
    reg = createRegistry(true, reg.getName());
    std::vector<eng::Entity> bgs = makeBackgrounds(reg, w, c);
    eng::Entity baba = reg.spawnEntity();
    w.setFramerateLimit(60);

    reg.addComponent<rtp::Position>(baba, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(baba, rtp::Velocity(0, 0));
    reg.addComponent<rtp::Shooter>(baba, rtp::Shooter("../assets/bullet.png", 25.0, std::vector<float>({65, 25, 0})));
    reg.addComponent<rtp::Drawable>(baba, rtp::Drawable("../assets/platypus_spaceship.png", w, c, 1, sf::IntRect(0, 0, 65, 49), 0.005));
    reg.addComponent<rtp::Controllable>(baba, rtp::Controllable(w));

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        systems.controlSystem(reg);
        systems.positionSystem(reg);
        systems.controlFireSystem(reg);
        systems.shootSystem(reg);
        systems.clearSystem(reg);
        systems.backgroundSystem(reg);
        systems.drawSystem(reg);
        systems.playSoundSystem(reg);
        systems.displaySystem(reg);
    }
    return 0;
}