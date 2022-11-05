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

rtp::MainMenu::MainMenu(eng::RegistryManager &manager,
std::function<int(eng::RegistryManager&, bool, int)> &co,
eng::GraphicSystems &gfx, eng::TextureManager &textureManager):
_manager(manager), _singlePlayerBtnFct(co), _gfx(gfx),
_textureManager(textureManager)
{
    _manager.addRegistry("R1");
    setupRegistry(_manager.getTop());
    _addButtons(_manager.getTop());
    _addBackgrounds(_manager.getTop());
    _addEarth(_manager.getTop());
    
}

void rtp::MainMenu::_addEarth(eng::Registry &reg)
{
    eng::Entity bg = reg.spawnEntity();
    reg.addComponent<eng::Velocity>(bg, eng::Velocity(0, 0, 35));

    reg.addComponent<eng::Position>(bg, eng::Position(1920 / 2, 1300, 0));
    reg.addComponent<eng::Drawable>(bg, eng::Drawable(_textureManager.getTextureFromFile("assets/terre.png")));
    reg.getComponents<eng::Drawable>()[bg.getId()].value().sprite.setScale(2, 2);
    auto &draw = reg.getComponents<eng::Drawable>();
    int x = draw[bg.getId()].value().sprite.getTexture()->getSize().x / 2;
    int y = draw[bg.getId()].value().sprite.getTexture()->getSize().y / 2;
    draw[bg.getId()].value().sprite.setOrigin(x, y);
    draw[bg.getId()].value().protect = true;
}

void rtp::MainMenu::_addBackgrounds(eng::Registry &reg)
{
    eng::Entity bg = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    reg.addComponent<eng::Drawable>(bg, eng::Drawable(_textureManager.getTextureFromFile("assets/background.png")));
    reg.addComponent<rtp::Background>(bg, rtp::Background());
    eng::Entity bg2 = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg2, eng::Position(0, 0, 0));
    reg.addComponent<eng::Drawable>(bg2, eng::Drawable(_textureManager.getTextureFromFile("assets/middleground.png")));
    reg.addComponent<rtp::Background>(bg2, rtp::Background());
    eng::Entity bg3 = reg.spawnEntity();
    reg.addComponent<eng::Position>(bg3, eng::Position(0, 0, 0));
    reg.addComponent<eng::Drawable>(bg3, eng::Drawable(_textureManager.getTextureFromFile("assets/foreground.png")));
    reg.addComponent<rtp::Background>(bg3, rtp::Background());
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
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;
    std::function<int(eng::RegistryManager &)> chooseLvl = std::bind(&MainMenu::_chooseLvlBtn, this, _manager);

    r.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(chooseLvl, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable(_textureManager.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Singleplayer", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));

}

void rtp::MainMenu::_addButtonMultiplayer(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> multi = std::bind(&MainMenu::_MultiBtn, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(multi, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable(_textureManager.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Multiplayer", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));

}

void rtp::MainMenu::_addButtonExit(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> exit = std::bind(&MainMenu::_exitBtn, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable(_textureManager.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Quit Games", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 700, 0));

    
}

void rtp::MainMenu::_addButtonSettings(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> exit = std::bind(&MainMenu::_exitBtn, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(970, 700, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable(_textureManager.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    r.addComponent<eng::Position>(btntesxt, eng::Position(990, 700, 0));
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Options", "assets/MetroidPrimeHunters.ttf"));
}

int rtp::MainMenu::_exitBtn(eng::RegistryManager &reg)
{
    this->_gfx.closeWindow();
    return (0);
}

int rtp::MainMenu::_chooseLvlBtn(eng::RegistryManager &reg)
{
    rtp::ChooseLvl *cl = new rtp::ChooseLvl(_manager, this->_singlePlayerBtnFct, _textureManager);
    return (0);
}

int rtp::MainMenu::_MultiBtn(eng::RegistryManager &reg)
{
    _singlePlayerBtnFct(_manager, true, 1);
    return (0);
}