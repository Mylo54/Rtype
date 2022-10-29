/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ChooseLvl
*/

#include "ChooseLvl.hpp"

rtp::ChooseLvl::ChooseLvl(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&)> co) : _manager(manager), _singlePlayerBtnFct(co)
{
    _manager.addRegistry("lvl");
    _setupRegistry(_manager.getTop());
    _addButtons(_manager.getTop());
    std::cout << "call here" << std::endl;
}

rtp::ChooseLvl::~ChooseLvl()
{
}

void rtp::ChooseLvl::_setupRegistry(eng::Registry &reg)
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

void rtp::ChooseLvl::_addButtons(eng::Registry &r)
{
    _addButtonLvl1(r);
    _addButtonLvl2(r);
    _addButtonLvl3(r);
    _addButtonLvl4(r);
    _addButtonLvlFinal(r);
    _addBackgrounds(r);
}

void rtp::ChooseLvl::_addBackgrounds(eng::Registry &reg)
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

void rtp::ChooseLvl::_addButtonLvl1(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&ChooseLvl::_btnFctlvl1, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 1", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}

void rtp::ChooseLvl::_addButtonLvl2(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&ChooseLvl::_btnFctlvl2, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 2", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));

}

void rtp::ChooseLvl::_addButtonLvl3(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&ChooseLvl::_btnFctlvl3, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 3", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 700, 0));

}

void rtp::ChooseLvl::_addButtonLvl4(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&ChooseLvl::_btnFctlvl4, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 800, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 4", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 800, 0));

}

void rtp::ChooseLvl::_addButtonLvlFinal(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&ChooseLvl::_btnFctlvlB, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 900, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level Final", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 900, 0));

}

int rtp::ChooseLvl::_btnFctlvl1(eng::RegistryManager &reg)
{
    std::cout << "Choose Lvl" << std::endl;
    _singlePlayerBtnFct(_manager);
    return (0);
}

int rtp::ChooseLvl::_btnFctlvl2(eng::RegistryManager &reg)
{
    std::cout << "Choose Lvl" << std::endl;
    _singlePlayerBtnFct(_manager);
    return (0);
}
int rtp::ChooseLvl::_btnFctlvl3(eng::RegistryManager &reg)
{
    std::cout << "Choose Lvl" << std::endl;
    _singlePlayerBtnFct(_manager);
    return (0);
}
int rtp::ChooseLvl::_btnFctlvl4(eng::RegistryManager &reg)
{
    std::cout << "Choose Lvl" << std::endl;
    _singlePlayerBtnFct(_manager);
    return (0);
}

int rtp::ChooseLvl::_btnFctlvlB(eng::RegistryManager &reg)
{
    std::cout << "Choose Lvl" << std::endl;
    _singlePlayerBtnFct(_manager);
    return (0);
}