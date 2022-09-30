/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/Config.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Main.hpp"
#include <string.h>
#include <cstdio>
#include <fstream>

std::string logPath = "";
extern std::string logPath;

class Position {
    public:
        Position(float _x, float _y, float _z): x(_x), y(_y), z(_z)
        {} 
        float x;
        float y;
        float z;
};

class Velocity {
    public:
        Velocity(float _x, float _y): x(_x), y(_y)
        {} 
        float x;
        float y;
};

class Drawable {
    public:
        Drawable(std::string textureFilePath, sf::RenderWindow &pwindow) : window(pwindow) 
        {
            texture->loadFromFile(textureFilePath);
            sprite.setTexture(*texture);
        }
        sf::RenderWindow &window;
        sf::Texture *texture = new sf::Texture;
        sf::Sprite sprite;
};


#include "SparseArray.hpp"
#include "Registry.hpp"
#include <string.h>

eng::Registry createRegistry(bool isDebugMode, std::string name)
{
    eng::Registry res;
    res.setName(name);
    eng::SparseArray<Position> position;
    eng::SparseArray<Velocity> velocity;
    eng::SparseArray<Drawable> drawable;

    if (isDebugMode) res.setDebugMode(true);
    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    return (res);
}

// Exemple of system
void position_system(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += vel.value().x;
            pos.value().y += vel.value().y;
        }
    }
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

// Not very working...
void draw_system(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &sprites = r.getComponents<Drawable>();

    // Clear
    for (int i = 0;i < sprites.size(); i++)
        if (sprites[i].has_value()) {
            sprites[i].value().window.clear(sf::Color::Red);
            break;
        }

    // Draw
    for (int i = 0; i < positions.size() && i < sprites.size(); i++) {
        auto &pos = positions[i];
        auto &spr = sprites[i];

        if (pos.has_value() && spr.has_value()) {
            spr.value().sprite.setPosition({pos.value().x, pos.value().y});
            spr.value().window.draw(spr.value().sprite);
        }
    }

    // Display
    for (int i = 0;i < sprites.size(); i++) {
        auto &spr = sprites[i];

        if (spr.has_value()) {
            spr.value().window.display();
            break;
        }
    }
}

void log_system(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            std::cout << i << ": pos = {" << pos.value().x << ", " << pos.value().y;
            std::cout << ", " << pos.value().z << "}, vel = {" << vel.value().x;
            std::cout << ", " << vel.value().y << "}" << std::endl;
        }
    }
}

int main(int argc, char **argv)
{
    eng::Registry reg;

    reg.setName("Registry1");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            reg.setDebugMode(true);
            newLogPath();
        }
    reg = createRegistry(true, reg.getName());
    eng::Entity baba = reg.spawnEntity();
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "Rutabaga");
    w.setFramerateLimit(60);
    
    //test sfml
    /*
    sf::Texture txt;
    txt.loadFromFile("../assets/samus2.png");
    sf::Sprite spr(txt);
    */
    reg.addComponent<Position>(baba, Position(0, 0, 0));
    reg.addComponent<Velocity>(baba, Velocity(5, 5));
    reg.addComponent<Position>(boubou, Position(5, 5, 0));
    reg.addComponent<Velocity>(boubou, Velocity(0, 0));

    std::cout << "baba id =" << baba.getId() << std::endl;
    std::cout << "boubou id =" << boubou.getId() << std::endl;
    std::cout << "baba pos:" << reg.getComponents<Position>()[baba.getId()].value().x;
    std::cout << ", " << reg.getComponents<Position>()[baba.getId()].value().y << std::endl;
    position_system(reg);
    std::cout << "baba pos:" << reg.getComponents<Position>()[baba.getId()].value().x;
    std::cout << ", " << reg.getComponents<Position>()[baba.getId()].value().y << std::endl;
    reg.addComponent<Velocity>(baba, Velocity(1, 1));
    reg.addComponent<Drawable>(baba, Drawable("../assets/samus2.png", w));

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        position_system(reg);
        draw_system(reg);
    }
    return 0;
}