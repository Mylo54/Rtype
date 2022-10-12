/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystems
*/

#include "ServerSystems.hpp"

rtp::ServerSystems::ServerSystems(boost::asio::ip::udp::socket &socket,
    std::mutex &mutex, std::vector<rtp::networkPayload> &listDataRec,
    std::vector<boost::asio::ip::udp::endpoint> &endpoints) : _socket(socket),
    _mutex(mutex), _listDataRec(listDataRec), _endpoints(endpoints)
{
}

rtp::ServerSystems::~ServerSystems()
{
}

void rtp::ServerSystems::addEndpoint(std::string address, int port)
{
    _endpoints.push_back({boost::asio::ip::make_address(address), static_cast<boost::asio::ip::port_type>(port)});
}

void rtp::ServerSystems::removeEndPoint(std::string address, int port)
{
    auto it = _endpoints.begin();
    bool found = false;

    while (it != _endpoints.end()) {
        if (it->address() == boost::asio::ip::make_address(address)
            && it->port() == static_cast<boost::asio::ip::port_type>(port)) {
            found = true;
            break;
        }
        it++;
    }
    if (found)
        _endpoints.erase(it);
}

void rtp::ServerSystems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += vel.value().x;
            pos.value().y += vel.value().y;
        }
    }
}

void rtp::ServerSystems::controlSystem(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            // up and down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                ctrl.value().yAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                ctrl.value().yAxis = 1;
            else
                ctrl.value().yAxis = 0;
            
            // left and right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                ctrl.value().xAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                ctrl.value().xAxis = 1;
            else
                ctrl.value().xAxis = 0;
            
            // shoot
            ctrl.value().shoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }
    }
}

void rtp::ServerSystems::controlMovementSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * 2;
            vel.value().x += (vel.value().x > 0) ? -1 : 0;
            vel.value().x += (vel.value().x < 0) ? 1 : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * 2;
            vel.value().y += (vel.value().y > 0) ? -1 : 0;
            vel.value().y += (vel.value().y < 0) ? 1 : 0;
        }
    }
}

void rtp::ServerSystems::controlFireSystem(eng::Registry &r)
{
    auto &shooters = r.getComponents<Shooter>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < shooters.size(); i++) {
        auto &sht = shooters[i];
        auto &ctrl = controllables[i];

        if (sht.has_value() && ctrl.has_value()) {
            sht.value().shoot = ctrl.value().shoot;
        }
    }
}

void rtp::ServerSystems::sendData(eng::Registry &r)
{
    auto &ps = r.getComponents<Position>();
    auto &vs = r.getComponents<Velocity>();
    auto &playerStats = r.getComponents<PlayerStats>();
    auto &enemyStats = r.getComponents<EnemyStats>();
    auto &sc = r.getComponents<Synced>();
    boost::array<synced_component, 1> dataTbs;

    for (int i = 0; i < ps.size() && i < vs.size() && i < playerStats.size(); i++) {
        // Send player infos
        // (not checking if ps and vs have values so it's dangerous O_o)
        if (playerStats[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &id_sync = sc[i].value();
            auto &player = playerStats[i].value();
            // Send thoses values to each client
            
            dataTbs = {POSITION, id_sync.id, p};
            sendSyncedDataToAll(dataTbs);
            dataTbs = {VELOCITY, id_sync.id, v};
            sendSyncedDataToAll(dataTbs);
            dataTbs = {PLAYER_STATS, id_sync.id, player};
            sendSyncedDataToAll(dataTbs);
        }
    }
    for (int i = 0; i < ps.size() && i < vs.size() && i < enemyStats.size(); i++) {
        // Same but for enemies
        if (enemyStats[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &enm = enemyStats[i].value();
            // Send thoses values to each client

           
        }
        // Then send shot events and from which player they arrived from
    }
}

void rtp::ServerSystems::sendSyncedDataToAll(boost::array<synced_component, 1> dataTbs)
{
    for (int i = 0; i < _endpoints.size(); i++) {
        _socket.send_to(boost::asio::buffer(dataTbs), _endpoints[i]);
    }
}

void rtp::ServerSystems::receiveData(eng::Registry &r)
{
    int e = 0;
    _mutex.lock();
    while (_listDataRec.size() > 0) {
        e = _getSyncedEntity(r, (size_t)_listDataRec.back().body);
        if (e != -1) {
            if (_listDataRec.back().ACTION_NAME == SHOT) {
                r.getComponents<Controllable>()[e].value().shoot = true;
            }
            if (_listDataRec.back().ACTION_NAME == LEFT) {
                r.getComponents<Controllable>()[e].value().xAxis = -1;
            }
            if (_listDataRec.back().ACTION_NAME == RIGHT) {
                r.getComponents<Controllable>()[e].value().xAxis = +1;
            }
            if (_listDataRec.back().ACTION_NAME == UP) {
                r.getComponents<Controllable>()[e].value().yAxis = -1;
            }
            if (_listDataRec.back().ACTION_NAME == DOWN) {
                r.getComponents<Controllable>()[e].value().yAxis = +1;
            }
        }
        _listDataRec.pop_back();

    }
    _mutex.unlock();
}

int rtp::ServerSystems::_getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<Synced>();

    for (int i = 0; i < synceds.size(); i++) {
        if (synceds[i].has_value() == true) {
            if (synceds[i].value().id == syncId) {
                return i;
            }
        }
    }
    return -1;
}