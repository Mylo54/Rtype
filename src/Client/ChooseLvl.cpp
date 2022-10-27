/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ChooseLvl
*/

#include "ChooseLvl.hpp"

rtp::ChooseLvl::ChooseLvl(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&)> co) : _manager(manager), _singlePlayerBtnFct(co)
{
}

rtp::ChooseLvl::~ChooseLvl()
{
    _addButtons(_manager.getTop());
}


void rtp::ChooseLvl::_addButtons(eng::Registry &r)
{
    _addButtonLvl1(r);
    _addButtonLvl2(r);
    _addButtonLvl3(r);
    _addButtonLvl4(r);
    _addButtonLvlFinal(r);
}

void rtp::ChooseLvl::_addButtonLvl1(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

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

    r.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 2", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}

void rtp::ChooseLvl::_addButtonLvl3(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    r.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 3", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}
void rtp::ChooseLvl::_addButtonLvl4(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    r.addComponent<eng::Position>(btn, eng::Position(700, 800, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level 4", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}

void rtp::ChooseLvl::_addButtonLvlFinal(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    r.addComponent<eng::Position>(btn, eng::Position(700, 900, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(_singlePlayerBtnFct, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Level Final", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}
