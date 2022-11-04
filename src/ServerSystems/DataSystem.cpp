/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataSystem
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::sendData(eng::Registry &r)
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
                _addToPayload(payload, {POSITION, (int)p.x, (int)p.y, (int)p.z, (int)p.rotation});
            }
            if (i < vs.size() && vs[i].has_value()) {
                auto &v = vs[i].value();
                _addToPayload(payload, {VELOCITY, (int)v.x, (int)v.y, (int)v.angular});
            }
            if (i < playerStats.size() && playerStats[i].has_value()) {
                auto &p = playerStats[i].value();
                _addToPayload(payload, {PLAYER_STATS, p.playerId, p.damage, p.lives, p.score});
            }
            if (i < enemyStats.size() && enemyStats[i].has_value()) {
                auto &e = enemyStats[i].value();
                _addToPayload(payload, {ENEMY_STATS, e.health, e.enemyType});
            }
            if (i < bonuses.size() && bonuses[i].has_value()) {
                auto &b = bonuses[i].value();
                _addToPayload(payload, {BONUS, b.type});
            }
        }
    }
    _sendDataToAll(payload);
}

void rtp::ServerSystems::_addToPayload(std::vector<int> &payload,
std::vector<int> toAdd)
{
    for (int i = 0; i < toAdd.size(); i++)
        payload.push_back(toAdd[i]);
    payload[1] += toAdd.size();
}

void rtp::ServerSystems::_sendDataToAll(std::vector<int> &vector)
{
    // for (auto it = vector.begin(); it != vector.end(); it++) {
    //     std::cout << *it << std::endl;
    // }
    for (int i = 0; i < _endpoints.size(); i++) {
        //std::cout << "endpoint[" << i << "] : " << _endpoints[i] << std::endl;
        _socket.send_to(boost::asio::buffer(vector), _endpoints[i]);
    } //std::cout << "endSyncedDataToAll ENDED" << std::endl;
}

void rtp::ServerSystems::receiveData(eng::Registry &r)
{
    int e = 0;

    _mutex.lock();
    while (!_listDataRec.empty()) {
        // Dump invalid packets
        if (_listDataRec.back()[0] != 1450) {
            _listDataRec.pop_back();
            continue;
        }

        // Emplace valid ones
        e = _getSyncedEntity(r, _listDataRec.back()[3]);
        auto &ctrl = r.getComponents<Controllable>()[e].value();
        ctrl.xAxis = _listDataRec.back()[4];
        ctrl.yAxis = _listDataRec.back()[5];
        std::cout << "test 66" << std::endl;
        if (ctrl.yAxis == -1)
            std::cout << "Button pressed on client ctrl.yaxis = " << ctrl.yAxis << std::endl;
        ctrl.shoot = (_listDataRec.back()[6] == 1);
        _listDataRec.pop_back();
    }
    _mutex.unlock();
}