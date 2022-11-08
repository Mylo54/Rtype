/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MainMenu
*/

#include "MainMenu.hpp"

rtp::MainMenu::MainMenu(rtp::scene_package_t &pack, eng::RegistryManager &manager, std::function<int(eng::RegistryManager&, bool, int, int)> &co):
                        AScene(pack), _manager(manager), _singlePlayerBtnFct(co)
{
    _manager.addRegistry("MainMenu");
    setupRegistry();
    _addButtons();
    _addBackgrounds();
    _addEarth();   
}

rtp::MainMenu::~MainMenu()
{
}

void rtp::MainMenu::setupRegistry()
{
    _reg.registerComponents(eng::SparseArray<eng::Velocity>());
    _reg.registerComponents(eng::SparseArray<eng::Position>());
    _reg.registerComponents(eng::SparseArray<eng::Drawable>());
    _reg.registerComponents(eng::SparseArray<eng::Sound>());
    _reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    _reg.registerComponents(eng::SparseArray<eng::Writable>());
    _reg.registerComponents(eng::SparseArray<eng::Music>());
    _reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    _reg.registerComponents(eng::SparseArray<eng::RigidBody>());
    // _reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    // _reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    // _reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    // _reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    // _reg.registerComponents(eng::SparseArray<rtp::Background>());
    // _reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    // _reg.registerComponents(eng::SparseArray<rtp::Synced>());
    // _reg.registerComponents(eng::SparseArray<rtp::Button>());
    // _reg.registerComponents(eng::SparseArray<rtp::Bonus>());
}

void rtp::MainMenu::_addButtons()
{
    _addButtonStartLocal();
    _addButtonMultiplayer();
    _addButtonSettings();
    _addButtonExit();
}

void rtp::MainMenu::_addButtonStartLocal()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 2;
    std::function<int(eng::RegistryManager &)> chooseLvl = std::bind(&MainMenu::_chooseLvlBtn, this, _manager);

    _reg.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    // _reg.addComponent<rtp::Button>(btn, rtp::Button(chooseLvl, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Singleplayer", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));
}

void rtp::MainMenu::_addButtonExit()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> exit = std::bind(&MainMenu::_exitBtn, this, _manager);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 700, 0));
    // _reg.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));
    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Quit Games", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 700, 0));
}

void rtp::MainMenu::_addButtonMultiplayer()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;    

    std::function<int(eng::RegistryManager &)> multi = std::bind(&MainMenu::_MultiBtn, this, _manager);
    _reg.addComponent<eng::Position>(btn, eng::Position(700, 600, 0));
    // _reg.addComponent<rtp::Button>(btn, rtp::Button(multi, 0, 0, 128 * 4, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Multiplayer", "assets/MetroidPrimeHunters.ttf"));
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(720, 600, 0));
}

void rtp::MainMenu::_addButtonSettings()
{
    eng::Entity btn = _reg.spawnEntity();
    eng::Entity btntesxt = _reg.spawnEntity();
    int scale = 4;

    std::function<int(eng::RegistryManager &)> exit = std::bind(&MainMenu::_exitBtn, this, _manager);
    _reg.addComponent<eng::Position>(btn, eng::Position(970, 700, 0));
    // _reg.addComponent<rtp::Button>(btn, rtp::Button(exit, 0, 0, 128 * 1.9, 32 * 1.5));
    _reg.addComponent<eng::Drawable>(btn, eng::Drawable(_texture.getTextureFromFile("assets/button.png"), 3, {0, 0, 128, 32}));

    _reg.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(1.9, 1.5);
    _reg.addComponent<eng::Position>(btntesxt, eng::Position(990, 700, 0));
    _reg.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "Options", "assets/MetroidPrimeHunters.ttf"));
}

void rtp::MainMenu::_addBackgrounds()
{
    eng::Entity bg = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
    // _reg.addComponent<rtp::Background>(bg, rtp::Background());
    eng::Entity bg2 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg2, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg2, eng::Drawable(_texture.getTextureFromFile("assets/middleground.png")));
    // _reg.addComponent<rtp::Background>(bg2, rtp::Background());
    eng::Entity bg3 = _reg.spawnEntity();
    _reg.addComponent<eng::Position>(bg3, eng::Position(0, 0, 0));
    _reg.addComponent<eng::Drawable>(bg3, eng::Drawable(_texture.getTextureFromFile("assets/foreground.png")));
    // _reg.addComponent<rtp::Background>(bg3, rtp::Background());
}

void rtp::MainMenu::_addEarth()
{
    eng::Entity bg = _reg.spawnEntity();
    _reg.addComponent<eng::Velocity>(bg, eng::Velocity(0, 0, 35));

    _reg.addComponent<eng::Position>(bg, eng::Position(1920 / 2, 1300, 0));
    _reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/terre.png")));
    _reg.getComponents<eng::Drawable>()[bg.getId()].value().sprite.setScale(2, 2);
    auto &draw = _reg.getComponents<eng::Drawable>();
    int x = draw[bg.getId()].value().sprite.getTexture()->getSize().x / 2;
    int y = draw[bg.getId()].value().sprite.getTexture()->getSize().y / 2;
    draw[bg.getId()].value().sprite.setOrigin(x, y);
    draw[bg.getId()].value().protect = true;
}

int rtp::MainMenu::_exitBtn(eng::RegistryManager &regMan)
{
    _graphic.closeWindow();
    return (0);
}

int rtp::MainMenu::_chooseLvlBtn(eng::RegistryManager &reg)
{
    // rtp::ChooseLvl *cl = new rtp::ChooseLvl(_manager, this->_singlePlayerBtnFct, _texture);
    return (0);
}

int rtp::MainMenu::_MultiBtn(eng::RegistryManager &reg)
{
    //MapVoter *mv = new MapVoter(_manager, _singlePlayerBtnFct, _texture);
    _singlePlayerBtnFct(_manager, true, 1, 0);
    return (0);
}
