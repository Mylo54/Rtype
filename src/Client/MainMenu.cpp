/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

rtp::MainMenu::MainMenu(eng::RegistryManager &manager) : _manager(manager)
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addButton(_manager.getTop());
}

void rtp::MainMenu::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Button>());
    reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    reg.registerComponents(eng::SparseArray<rtp::Writable>());
}

rtp::MainMenu::~MainMenu()
{
}

void rtp::MainMenu::_btnFuncExit(void)
{
    std::cout << "Hello World!" << std::endl;
}

void rtp::MainMenu::_btnFuncStart(void)
{
    std::cout << "Hello World!" << std::endl;
}

void btn_func(eng::RegistryManager &manager)
{
    rtp::Game game(manager);
}


void rtp::MainMenu::_addButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<rtp::Position>(btn, rtp::Position(100, 100, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(btn_func, 0, 0, 128 * scale, 32 * scale));
    r.addComponent<rtp::Writable>(btn, rtp::Writable("Button", "Hello Chloe"));
    r.addComponent<rtp::Drawable>(btn, rtp::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<rtp::Drawable>()[btn.getId()].value().sprite.setScale(4, 4);
}