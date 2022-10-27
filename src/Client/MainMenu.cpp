/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

int btnFuncStart(eng::RegistryManager &manager)
{
    //rtp::Game game(manager);

    return 0;
}

rtp::MainMenu::MainMenu(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&)> co) : _manager(manager), _singlePlayerBtnFct(co)
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addButtons(_manager.getTop());
    _addBackgrounds(_manager.getTop());
}

void rtp::MainMenu::_addBackgrounds(eng::Registry &reg)
{
    eng::Entity bg = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    reg.addComponent<rtp::Background>(bg, rtp::Background("assets/foreground.png"));
    eng::Entity bg2 = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg2, eng::Position(-50, -50, 0));
    reg.addComponent<rtp::Background>(bg2, rtp::Background("assets/middleground.png"));
    eng::Entity bg3 = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg3, eng::Position(-50, -50, 0));
    reg.addComponent<rtp::Background>(bg3, rtp::Background("assets/background.png"));
}

void rtp::MainMenu::_setupRegistry(eng::Registry &reg)
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

rtp::MainMenu::~MainMenu()
{
}

void rtp::MainMenu::_addButtons(eng::Registry &r)
{
    _addButtonStartLocal(r);
    _addButtonMultiplayer(r);
    _addButtonSettings(r);
    _addButtonExit(r);
}

void rtp::MainMenu::_addButtonStartLocal(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 2;

    r.addComponent<eng::Position>(btn, eng::Position(100, 100, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "Singleplayer", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

void rtp::MainMenu::_addButtonMultiplayer(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(100, 250, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "Multiplayer", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
}

void rtp::MainMenu::_addButtonExit(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(100, 400, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(btnFuncStart, 0, 0, 128 * 1.9, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "Quit Games", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
}

void rtp::MainMenu::_addButtonSettings(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(370, 400, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(btnFuncStart, 0, 0, 128 * 1.9, 32 * 1.5));
    r.addComponent<eng::Writable>(btn, eng::Writable("Button", "Options", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
}
