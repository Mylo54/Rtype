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
        Drawable(std::string textureFilePath, sf::RenderWindow &pwindow, bool pSheetDirection = 0, sf::IntRect rect = {0, 0, 0, 0}) : window(pwindow) 
        {
            sheetDirection = pSheetDirection;
            texture->loadFromFile(textureFilePath);
            sprite.setTexture(*texture);
            sizeX = texture->getSize().x;
            sizeY = texture->getSize().y;
            if (sheetDirection != 0)
                sprite.setTextureRect(rect);
        }
        int sheetDirection;
        sf::RenderWindow &window;
        sf::Texture *texture = new sf::Texture;
        sf::Sprite sprite;
        int sizeX;
        int sizeY;
};

class Controllable {
    public:
        Controllable(sf::RenderWindow &pwindow): window(pwindow)
        {
        }
        sf::RenderWindow &window;
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
    eng::SparseArray<Controllable> control;

    if (isDebugMode) res.setDebugMode(true);
    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    res.registerComponents(control);
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

    // Draw & update sheets
    for (int i = 0; i < positions.size() && i < sprites.size(); i++) {
        auto &pos = positions[i];
        auto &spr = sprites[i];

        if (pos.has_value() && spr.has_value()) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection == 1) {
                rect.left += rect.width;
                if (rect.left >= spr.value().sizeX)
                    rect.left = 0;
            }
            spr.value().sprite.setTextureRect(rect);
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

// This will change
void control_system(eng::Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vel.value().x = vel.value().x - 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                vel.value().x = vel.value().x + 1;
            else {
                if (vel.value().x > 0)
                    vel.value().x--;
                else if (vel.value().x < 0)
                    vel.value().x++;
            }
            
            // Up & Down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                vel.value().y = vel.value().y - 1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                vel.value().y = vel.value().y + 1;
            else {
                if (vel.value().y > 0)
                    vel.value().y--;
                else if (vel.value().y < 0)
                    vel.value().y++;
            }
        }
    }
}

int main(int argc, char **argv)
{
    eng::Registry reg;
    reg.setName("Registry1");
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) reg.setDebugMode(true);
    reg = createRegistry(false, reg.getName());
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
    reg.addComponent<Velocity>(baba, Velocity(0, 0));
    reg.addComponent<Drawable>(baba, Drawable("../assets/platypus_spaceship.png", w, 1, sf::IntRect(0, 0, 65, 49)));
    reg.addComponent<Controllable>(baba, Controllable(w));

    while (w.isOpen())
    {
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        control_system(reg);
        position_system(reg);
        draw_system(reg);
    }
    return 0;
}