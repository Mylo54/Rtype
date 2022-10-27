/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"

rtp::PauseMenu::PauseMenu(eng::RegistryManager &manager) : _manager(manager)
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addButton(_manager.getTop());
}

void rtp::PauseMenu::_setupRegistry(eng::Registry &reg)
{
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

int startBtn(eng::RegistryManager &manager)
{
    //rtp::Game game(manager);
    return 0;
}

void rtp::PauseMenu::_addButton(eng::Registry &r)
{
    _addResumeButton(r);
    _addSettingsButton(r);
    _addMainMenuButton(r);
    _addExitButton(r);
}

void rtp::PauseMenu::_addResumeButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(732, 442, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "RESUME", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

void rtp::PauseMenu::_addSettingsButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(732, 491, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "SETTINGS", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

void rtp::PauseMenu::_addMainMenuButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(732, 540, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "MAIN MENU", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

void rtp::PauseMenu::_addExitButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(732, 589, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "EXIT", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

rtp::PauseMenu::~PauseMenu()
{
}
