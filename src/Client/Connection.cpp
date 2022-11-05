/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Connection
*/

#include "Connection.hpp"

rtp::Connection::Connection(eng::RegistryManager &manager,
eng::TextureManager &textureManager):
_manager(manager), _textureManager(textureManager)
{
    _manager.addRegistry("Connection");
    setupRegistry(_manager.getTop());
    //_addButtonStart(_manager.getTop());
    _addBackgrounds(_manager.getTop());
}

rtp::Connection::~Connection()
{
}

void rtp::Connection::_addBackgrounds(eng::Registry &reg)
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

void rtp::Connection::_addButtonStart(eng::Registry &r)
{
    eng::Entity btn = r.spawnEntity();
    eng::Entity btntesxt = r.spawnEntity();
    int scale = 2;

    std::function<int(eng::RegistryManager &)> lvl = std::bind(&Connection::_btnFctStart, this, _manager);
    r.addComponent<eng::Position>(btn, eng::Position(700, 500, 0));
    r.addComponent<rtp::Button>(btn, rtp::Button(lvl, 0, 0, 128 * 4, 32 * 1.5));
    r.addComponent<eng::Drawable>(btn, eng::Drawable("assets/button.png", 3, {0, 0, 128, 32}));

    r.getComponents<eng::Drawable>()[btn.getId()].value().sprite.setScale(4, 1.5);
    r.addComponent<eng::Writable>(btntesxt, eng::Writable("Button", "GO", "assets/MetroidPrimeHunters.ttf"));
    r.addComponent<eng::Position>(btntesxt, eng::Position(720, 500, 0));
}

int rtp::Connection::_btnFctStart(eng::RegistryManager &reg)
{
    return (0);
}

eng::Entity rtp::Connection::addPlayer(eng::Registry &reg, int playerId, int syncId)
{
    eng::Entity player = reg.spawnEntity();

    reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    reg.addComponent<eng::Velocity>(player, eng::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    reg.addComponent<eng::Drawable>(player, eng::Drawable("assets/players.png", 1, rect, 0.10));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    reg.addComponent<eng::RectCollider>(player, eng::RectCollider(40, 16));

    std::cout << "You are player " << playerId << std::endl;
    return player;
}