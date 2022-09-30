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

// Every "common type" should be typedefined
typedef std::vector<float> position_t;
typedef std::vector<float> velocity_t;

eng::Registry createRegistry()
{
    eng::Registry res;
    eng::SparseArray<position_t> position;
    eng::SparseArray<velocity_t> velocity;
    eng::SparseArray<sf::Sprite> drawable;

    res.registerComponents(position);
    res.registerComponents(velocity);
    res.registerComponents(drawable);
    return (res);
}

// Exemple of system
void position_system(eng::Registry &r)
{
    auto &positions = r.getComponents<position_t>();
    auto &velocities = r.getComponents<velocity_t>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            std::cout << "they have a value" << std::endl;
            pos.value()[0] += vel.value()[0];
            pos.value()[1] += vel.value()[1];
            std::cout << "vel value 0 = " << vel.value()[0] << std::endl;
        }
    }
}

// Not very working...
int main(int argc, char **argv)
{
    eng::Registry reg = createRegistry();
    eng::Entity baba = reg.spawnEntity();
    eng::Entity boubou = reg.spawnEntity();

    // std::cout << reg.getDebugMode() << std::endl;
    // for (int i = 1; i < argc; i++)
    //     if (strcmp(argv[i],"-debug") == 0)
    //         reg.setDebugMode(true);
    // std::cout << reg.getDebugMode() << std::endl;
    reg.addComponent<position_t>(baba, {0, 0, 0});
    reg.addComponent<velocity_t>(baba, {5, 5});
    reg.addComponent<position_t>(boubou, {5, 5, 0});
    reg.addComponent<velocity_t>(boubou, {0, 0});

    // std::cout << "baba's vel is at:" << reg.getComponents<velocity_t>()[baba.getId()].value()[0];
    // std::cout << ", " << reg.getComponents<velocity_t>()[baba.getId()].value()[1] << std::endl;
    // position_system(reg);
    // std::cout << "baba is at:" << reg.getComponents<position_t>()[baba.getId()].value()[0];
    // std::cout << ", " << reg.getComponents<position_t>()[baba.getId()].value()[1] << std::endl;
    return 0;
}