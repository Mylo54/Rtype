/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** PauseMenu
*/

#include "PauseMenu.hpp"

rtp::PauseMenu::PauseMenu(eng::RegistryManager &manager, eng::GraphicSystems &gfx) : _manager(manager), _gfx(gfx)
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addButton(_manager.getTop());
    _addBackgrounds(_manager.getTop());
}

int _resumeBtn(eng::RegistryManager &reg)
{
    reg.popRegistry();
    return (0);
}

void rtp::PauseMenu::_addBackgrounds(eng::Registry &reg)
{
    eng::Entity bg = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    reg.addComponent<rtp::Background>(bg, rtp::Background("assets/PM_bckgrd.png"));
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
    eng::Entity btntext = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(832, 442, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_resumeBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    r.addComponent<eng::Writable>(btntext, eng::Writable("Button", "RESUME", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntext, eng::Position(897, 445, 0));
}

void rtp::PauseMenu::_addSettingsButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntext = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(832, 491, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    r.addComponent<eng::Writable>(btntext, eng::Writable("Button", "OPTIONS", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntext, eng::Position(897, 494, 0));
}

void rtp::PauseMenu::_addMainMenuButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntext = r.spawnEntity();
    int scale = 4;

    r.addComponent<eng::Position>(btn, eng::Position(832, 540, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(startBtn, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    r.addComponent<eng::Writable>(btntext, eng::Writable("Button", "MAIN MENU", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntext, eng::Position(880, 543, 0));
}

void rtp::PauseMenu::_addExitButton(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntext = r.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> exit = std::bind(&PauseMenu::_exitBtn, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(832, 589, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 2, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(2, 1.5);
    r.addComponent<eng::Writable>(btntext, eng::Writable("Button", "QUIT GAME", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntext, eng::Position(882, 592, 0));
}

int rtp::PauseMenu::_exitBtn(eng::RegistryManager &reg)
{
    this->_gfx.closeWindow();
    return (0);
}

rtp::PauseMenu::~PauseMenu()
{
}
