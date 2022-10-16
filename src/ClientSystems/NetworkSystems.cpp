/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkSystems
*/

#include "NetworkSystems.hpp"

rtp::NetworkSystems::NetworkSystems(std::string address, int port,
boost::asio::ip::udp::socket &socket): _socket(socket)
{
    _endpoint = {boost::asio::ip::make_address(address), static_cast<boost::asio::ip::port_type>(port)};
}

rtp::NetworkSystems::~NetworkSystems()
{
}

void rtp::NetworkSystems::sendData(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();
    auto &synceds = r.getComponents<Synced>();
    boost::array<inputPayload_t, 1UL> data;

    for (int i = 0; i < controllables.size() && i < synceds.size(); i++) {
        auto ctrl = controllables[i];
        auto sync = synceds[i];

        if (ctrl.has_value() && sync.has_value()) {
            data[0].syncId = sync.value().id;
            if (ctrl.value().shoot) {
                data[0].ACTION_NAME = SHOT;
                _socket.send_to(boost::asio::buffer(data), _endpoint);
            }
            if (ctrl.value().xAxis > 0)
                data[0].ACTION_NAME = RIGHT;
            else if (ctrl.value().xAxis < 0)
                data[0].ACTION_NAME = LEFT;
            else
                data[0].ACTION_NAME = XSTILL;
            _socket.send_to(boost::asio::buffer(data), _endpoint);
            if (ctrl.value().yAxis > 0)
                data[0].ACTION_NAME = DOWN;
            else if (ctrl.value().yAxis < 0)
                data[0].ACTION_NAME = UP;
            else
                data[0].ACTION_NAME = YSTILL;
            _socket.send_to(boost::asio::buffer(data), _endpoint);
        }
    }
}

void rtp::NetworkSystems::receiveData(eng::Registry &r)
{
    int e = 0;
    bool toBuild = false;

    while (true) {
        _socket.receive(boost::asio::buffer(_dataBuffer));
        if (_dataBuffer[0].COMPONENT_NAME == END_PACKET)
            return;
        auto &data = _dataBuffer[0];
        e = _getSyncedEntity(r, data.syncId);
        toBuild = false;
        if (e == -1) {
            toBuild = true;
            e = r.spawnEntity().getId();
            r.addComponent<Synced>(eng::Entity(e), Synced(data.syncId));
        }
        if (_dataBuffer[0].COMPONENT_NAME == POSITION)
            r.emplaceComponent<Position>(eng::Entity(e), Position(data.valueA, data.valueB, data.valueC));
        if (_dataBuffer[0].COMPONENT_NAME == VELOCITY)
            r.emplaceComponent<Velocity>(eng::Entity(e), Velocity(data.valueA, data.valueB));
        if (data.COMPONENT_NAME == ENEMY_STATS) {
            r.emplaceComponent<EnemyStats>(eng::Entity(e), EnemyStats(data.valueB, data.valueA));
            if (toBuild)
                _completeEnemy(r, e);
        }
        if (data.COMPONENT_NAME == PLAYER_STATS) {
            r.emplaceComponent<PlayerStats>(eng::Entity(e), PlayerStats(data.valueA, data.valueB, data.valueC));
            if (toBuild)
                _completePlayer(r, e);
        }

    }
}

int rtp::NetworkSystems::_getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<Synced>();

    for (int i = 0; i < synceds.size(); i++)
        if (synceds[i].has_value())
            if (synceds[i].value().id == syncId)
                return (i);
    return (-1);
}

void rtp::NetworkSystems::_completeEnemy(eng::Registry &r, int e)
{
    int type = r.getComponents<EnemyStats>()[e].value().enemyType;
    if (type == 0)
        r.emplaceComponent<Drawable>(eng::Entity(e), Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.005));
        r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40, 16));
}

void rtp::NetworkSystems::_completePlayer(eng::Registry &r, int e)
{
    int playerId = r.getComponents<PlayerStats>()[e].value().playerId;
    sf::IntRect rect = {0, 0, 60, 49};
    r.addComponent<rtp::Shooter>(eng::Entity(e), rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40, 16));
    if (playerId == 2)
        rect.top = 49;
    if (playerId == 3)
        rect.top = 98;
    if (playerId == 4)
        rect.top = 147;
    r.addComponent<rtp::Drawable>(eng::Entity(e), rtp::Drawable("assets/players.png", 1, rect, 0.10));
}
