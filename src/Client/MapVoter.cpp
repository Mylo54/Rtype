/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MapVoter
*/

#include "MapVoter.hpp"

rtp::MapVoter::MapVoter(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&, bool, int, int)> &co) : _manager(manager), _co(co)
{
    _manager.addRegistry("MapVoter");
    _setupRegistry(_manager.getTop());
    _addButtons(_manager.getTop());
    _addBackgrounds(_manager.getTop());
}

rtp::MapVoter::~MapVoter()
{
}


void rtp::MapVoter::_addBackgrounds(eng::Registry &reg)
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

void rtp::MapVoter::_setupRegistry(eng::Registry &reg)
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

void rtp::MapVoter::_addButtons(eng::Registry &r)
{
    _addButtonMap1(r);
    _addButtonMap2(r);
    _addButtonMap3(r);
}


void rtp::MapVoter::_addButtonMap1(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&MapVoter::_btnFctMap1, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Map 1", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));
}

void rtp::MapVoter::_addButtonMap2(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&MapVoter::_btnFctMap2, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Map 2", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));

}

void rtp::MapVoter::_addButtonMap3(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&MapVoter::_btnFctMap3, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Map 3", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 700, 0));

}

int rtp::MapVoter::_btnFctMap1(eng::RegistryManager &reg)
{
    _co(_manager, false, 1, 0);
    return (0);
}

int rtp::MapVoter::_btnFctMap2(eng::RegistryManager &reg)
{
    _co(reg, false, 2, 1);
    return (0);
}
int rtp::MapVoter::_btnFctMap3(eng::RegistryManager &reg)
{
    _co(_manager, false, 3, 2);
    return (0);
}