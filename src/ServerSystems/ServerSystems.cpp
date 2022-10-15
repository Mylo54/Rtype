/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystems
*/

#include "ServerSystems.hpp"

rtp::ServerSystems::ServerSystems(boost::asio::ip::udp::socket &socket,
    std::mutex &mutex, std::vector<rtp::inputPayload_t> &listDataRec,
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

void rtp::ServerSystems::playerLogSystem(eng::Registry &r)
{
    auto &ps = r.getComponents<Position>();
    auto &ss = r.getComponents<PlayerStats>();
    auto &cs = r.getComponents<Controllable>();
    auto &sys = r.getComponents<Synced>();

    for (int i = 0; i < ps.size() && i < ss.size() && cs.size() && i < sys.size(); i++) {
        if (ps[i].has_value() && cs[i].has_value() && ss[i].has_value() && sys[i].has_value()) {
            auto p = ps[i].value();
            auto c = cs[i].value();
            auto s = ss[i].value();
            auto sy = sys[i].value();

            // std::cout << "Player " << sy.id << " is at {" << p.x << ", ";
            // std::cout << p.y << "}" << std::endl;
        }
    }
}

void rtp::ServerSystems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += (vel.value().x * _delta * 20);
            pos.value().y += (vel.value().y * _delta * 20);
        }
    }
}

void rtp::ServerSystems::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<Position>();
    auto &ves = r.getComponents<Velocity>();
    auto &pls = r.getComponents<PlayerStats>();

    for (int i = 0; i < pos.size() && i < ves.size() && i < pls.size(); i++) {
        if (pos[i].has_value() && ves[i].has_value() && pls[i].has_value()) {
            auto &position = pos[i].value();
            auto &velocity = ves[i].value();
            auto &playerSt = pls[i].value();

            position.x = (position.x >= 1860) ? 1860 : position.x;
            position.x = (position.x < 0) ? 0 : position.x;
            position.y = (position.y >= 982) ? 982 : position.y;
            position.y = (position.y < 0) ? 0 : position.y;
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
    boost::array<server_payload_t, 1> dataTbs;

    for (int i = 0; i < ps.size() && i < vs.size() && i < playerStats.size() && i < sc.size(); i++) {
        if (playerStats[i].has_value() && sc[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &id_sync = sc[i].value();
            auto &player = playerStats[i].value();
            
            dataTbs[0].COMPONENT_NAME = PLAYER_STATS;
            dataTbs[0].valueA = player.playerId;
            dataTbs[0].valueB = player.damage;
            dataTbs[0].valueC = player.lives;
            dataTbs[0].syncId = id_sync.id;
            sendSyncedDataToAll(dataTbs);
            dataTbs[0].COMPONENT_NAME = POSITION;
            dataTbs[0].valueA = p.x;
            dataTbs[0].valueB = p.y;
            dataTbs[0].valueC = p.z;
            sendSyncedDataToAll(dataTbs);
            dataTbs[0].COMPONENT_NAME = VELOCITY;
            dataTbs[0].valueA = v.x;
            dataTbs[0].valueB = v.y;
            sendSyncedDataToAll(dataTbs);
        }
    }
    for (int i = 0; i < ps.size() && i < vs.size() && i < enemyStats.size() && i < sc.size(); i++) {
        if (enemyStats[i].has_value() && sc[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &enm = enemyStats[i].value();
            auto &id_sync = sc[i].value();

            dataTbs[0].COMPONENT_NAME = ENEMY_STATS;
            dataTbs[0].valueA = enm.enemyType;
            dataTbs[0].valueB = enm.health;
            dataTbs[0].syncId = id_sync.id;
            sendSyncedDataToAll(dataTbs);
            dataTbs[0].COMPONENT_NAME = POSITION;
            dataTbs[0].valueA = p.x;
            dataTbs[0].valueB = p.y;
            dataTbs[0].valueC = p.z;
            sendSyncedDataToAll(dataTbs);
            dataTbs[0].COMPONENT_NAME = VELOCITY;
            dataTbs[0].valueA = v.x;
            dataTbs[0].valueB = v.y;
            sendSyncedDataToAll(dataTbs);
        }
        // Then send shot events and from which player they arrived from
    }
    dataTbs[0].COMPONENT_NAME = END_PACKET;
    sendSyncedDataToAll(dataTbs);
}

void rtp::ServerSystems::sendSyncedDataToAll(boost::array<server_payload_t, 1> dataTbs)
{
    for (int i = 0; i < _endpoints.size(); i++)
        _socket.send_to(boost::asio::buffer(dataTbs), _endpoints[i]);
}

void rtp::ServerSystems::receiveData(eng::Registry &r)
{
    int e = 0;
    _mutex.lock();
    while (_listDataRec.size() > 0) {
        e = _getSyncedEntity(r, _listDataRec.back().syncId);
        if (e != -1) {
            if (_listDataRec.back().ACTION_NAME == SHOT)
                r.getComponents<Controllable>()[e].value().shoot = true;
            if (_listDataRec.back().ACTION_NAME == XSTILL)
                r.getComponents<Controllable>()[e].value().xAxis = 0;
            if (_listDataRec.back().ACTION_NAME == LEFT)
                r.getComponents<Controllable>()[e].value().xAxis = -1;
            if (_listDataRec.back().ACTION_NAME == RIGHT)
                r.getComponents<Controllable>()[e].value().xAxis = +1;
            if (_listDataRec.back().ACTION_NAME == YSTILL)
                r.getComponents<Controllable>()[e].value().yAxis = 0;
            if (_listDataRec.back().ACTION_NAME == UP)
                r.getComponents<Controllable>()[e].value().yAxis = -1;
            if (_listDataRec.back().ACTION_NAME == DOWN)
                r.getComponents<Controllable>()[e].value().yAxis = +1;
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

void rtp::ServerSystems::updDeltaTime()
{
    std::chrono::_V2::steady_clock::time_point now = std::chrono::steady_clock::now();
    _delta = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
    lastUpdate = now;
}

void rtp::ServerSystems::limitTime()
{
    if ((_tps != 0) && ((1 / _tps) > _delta))
        sleep((1 / _tps) - _delta);
}