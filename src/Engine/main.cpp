/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "Registry.hpp"
#include "SparseArray.hpp"
#include "SFML/Graphics.hpp"
#include <string.h>

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

eng::Registry createRegistry()
{
    eng::Registry res;
    eng::SparseArray<Position> position;
    eng::SparseArray<Velocity> velocity;
    eng::SparseArray<sf::Sprite> drawable;

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

// Not very working...
int main(int argc, char **argv)
{
    eng::Registry reg = createRegistry();
    eng::Entity baba = reg.spawnEntity();
    eng::Entity boubou = reg.spawnEntity();

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
    return 0;
}