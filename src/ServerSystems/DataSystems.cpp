/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataSystems
*/

#include "DataSystems.hpp"

rtp::DataSystems::DataSystems(std::mutex &dataMutex,
std::vector<std::vector<int>> &payloadList,
boost::asio::ip::udp::socket &socket,
std::vector<boost::asio::ip::udp::endpoint> &endpoints):
_dataMutex(dataMutex), _payloadList(payloadList),
_socket(socket), _endpoints(endpoints)
{
}

rtp::DataSystems::~DataSystems()
{
}

static void addToPayload(std::vector<int> &payload,
std::vector<int> toAdd)
{
    for (int i = 0; i < toAdd.size(); i++)
        payload.push_back(toAdd[i]);
    payload[1] += toAdd.size();
}

void rtp::DataSystems::sendData(eng::Registry &r)
{
    std::vector<int> payload;
    auto &ps = r.getComponents<eng::Position>();
    auto &vs = r.getComponents<eng::Velocity>();
    auto &sc = r.getComponents<rtp::Synced>();
    auto &playerStats = r.getComponents<PlayerStats>();
    auto &enemyStats = r.getComponents<EnemyStats>();
    auto &bonuses = r.getComponents<Bonus>();

    // Header
    payload.push_back(1405);
    // Body size
    payload.push_back(0);
    for (int i = 0; i < sc.size(); i++) {
        // Entity header
        if (sc[i].has_value()) {
            payload.push_back(2002);
            payload.push_back(sc[i].value().id);
            if (i < ps.size() && ps[i].has_value()) {
                auto &p = ps[i].value();
                addToPayload(payload, {POSITION, (int)p.x, (int)p.y, (int)p.z, (int)p.rotation});
            }
            if (i < vs.size() && vs[i].has_value()) {
                auto &v = vs[i].value();
                addToPayload(payload, {VELOCITY, (int)v.x, (int)v.y, (int)v.angular});
            }
            if (i < playerStats.size() && playerStats[i].has_value()) {
                auto &p = playerStats[i].value();
                addToPayload(payload, {PLAYER_STATS, p.playerId, p.damage, p.lives, p.score});
            }
            if (i < enemyStats.size() && enemyStats[i].has_value()) {
                auto &e = enemyStats[i].value();
                addToPayload(payload, {ENEMY_STATS, e.health, e.enemyType});
            }
            if (i < bonuses.size() && bonuses[i].has_value()) {
                auto &b = bonuses[i].value();
                addToPayload(payload, {BONUS, b.type});
            }
        }
    }
    _sendDataToAll(payload);
}

void rtp::DataSystems::_sendDataToAll(std::vector<int> &vector)
{
    for (int i = 0; i < _endpoints.size(); i++)
        _socket.send_to(boost::asio::buffer(vector), _endpoints[i]);
}

static int getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<rtp::Synced>();

    for (int i = 0; i < synceds.size(); i++)
        if (synceds[i].has_value() == true)
            if (synceds[i].value().id == syncId)
                return i;
    return -1;
}

void rtp::DataSystems::receiveData(eng::Registry &r)
{
    int e = 0;

    _dataMutex.lock();
    while (!_payloadList.empty()) {
        // Dump invalid packets
        if (_payloadList.back()[0] != 1450) {
            _payloadList.pop_back();
            continue;
        }

        // Emplace valid ones
        e = getSyncedEntity(r, _payloadList.back()[3]);
        auto &ctrl = r.getComponents<Controllable>()[e].value();
        ctrl.xAxis = _payloadList.back()[4];
        ctrl.yAxis = _payloadList.back()[5];
        ctrl.shoot = (_payloadList.back()[6] == 1);
        _payloadList.pop_back();
    }
    _dataMutex.unlock();
}