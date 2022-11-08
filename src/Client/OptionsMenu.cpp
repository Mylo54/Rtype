/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** OptionsMenu
*/

#include "OptionsMenu.hpp"

rtp::OptionsMenu::OptionsMenu(eng::RegistryManager &manager,
eng::GraphicSystems &gfx, eng::TextureManager &textureManager) :
_manager(manager), _gfx(gfx), _textureManager(textureManager)
{
    _manager.addRegistry("OptionsMenu");
    setupRegistry(_manager.getTop());
    _addButton(_manager.getTop());
    _addBackground(_manager.getTop());
}

void rtp::OptionsMenu::_addButton(eng::Registry &r)
{
    _addMainMenuButton(r);
    _addExitButton(r);
}

void rtp::OptionsMenu::_addBackground(eng::Registry &reg)
{
    eng::Entity bg = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    reg.addComponent<eng::Drawable>(bg, eng::Drawable(_textureManager.getTextureFromFile("assets/middleground.png")));
    reg.addComponent<rtp::Background>(bg, rtp::Background());
    eng::Entity bg2 = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg2, eng::Position(0, 0, 0));
    reg.addComponent<eng::Drawable>(bg2, eng::Drawable(_textureManager.getTextureFromFile("assets/PM_bckgrd.png")));
    reg.addComponent<rtp::Background>(bg2, rtp::Background());
}

void rtp::OptionsMenu::_addMainMenuButton(eng::Registry &r)
{
    std::cout << "MainMenuButton" << std::endl;
}

void rtp::OptionsMenu::_addExitButton(eng::Registry &r)
{
    std::cout << "Exit Button" << std::endl;
}

rtp::OptionsMenu::~OptionsMenu()
{
}
