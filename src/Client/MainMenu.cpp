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
    //reg.registerComponents(eng::SparseArray<rtp::Position>());
    //reg.registerComponents(eng::SparseArray<rtp::Button>());
    //reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    //reg.registerComponents(eng::SparseArray<rtp::Writable>());


    reg.registerComponents(eng::SparseArray<eng::Velocity>());
    reg.registerComponents(eng::SparseArray<eng::Position>());
    reg.registerComponents(eng::SparseArray<eng::Drawable>());
    reg.registerComponents(eng::SparseArray<eng::Sound>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<eng::Writable>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
    reg.registerComponents(eng::SparseArray<rtp::Button>());
    reg.registerComponents(eng::SparseArray<eng::Music>());
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

void btnFuncStart(eng::RegistryManager &manager)
{
    rtp::Game game(manager);
}

void rtp::MainMenu::_addButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(100, 100, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(btnFuncStart, 0, 0, 128 * scale, 32 * scale));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "Start", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 4);
}