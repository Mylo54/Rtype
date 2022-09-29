/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "Registry.hpp"
#include "SparseArray.hpp"
#include "SFML/Graphics.hpp"

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

int main(void)
{
    eng::Registry reg = createRegistry();
    eng::Entity baba = reg.spawnEntity();
    eng::Entity boubou = reg.spawnEntity();

    reg.addComponent<position_t>(baba, {0, 0, 0});
    reg.addComponent<velocity_t>(baba, {5, 5});
    reg.addComponent<position_t>(boubou, {5, 5, 0});
    reg.addComponent<velocity_t>(boubou, {0, 0});

    std::cout << "baba is at:" << reg.getComponents<position_t>()[baba.getId()].value()[0];
    std::cout << ", " << reg.getComponents<position_t>()[baba.getId()].value()[1] << std::endl;
    return 0;
}