/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "iostream"
#include "Components/Components.hpp"
#include "Systems.hpp"
#include "Engine/Registry.hpp"
#include <string.h>

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

    if (isDebugMode) res.setDebugMode(true);
    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    res.registerComponents(control);
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

int main(int argc, char **argv)
{
    eng::Registry reg;
    rtp::Systems systems;

    reg.setName("Registry1");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            reg.setDebugMode(true);
            newLogPath();
        }
    reg = createRegistry(true, reg.getName());
    eng::Entity baba = reg.spawnEntity();
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");

    reg.addComponent<rtp::Position>(baba, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(baba, rtp::Velocity(0, 0));
    reg.addComponent<rtp::Drawable>(baba, rtp::Drawable("../assets/platypus_spaceship.png", w, 1, sf::IntRect(0, 0, 65, 49)));
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
        systems.drawSystem(reg);
    }
    return 0;
}