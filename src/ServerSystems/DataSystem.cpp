/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataSystem
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::_editDataTbs(rtp::server_payload_t &pl, int componentName, std::vector<float> values, int syncId, bool shot = false)
{
    pl.COMPONENT_NAME = componentName;
    pl.shot = shot;
    pl.syncId = syncId;
    pl.valueA = (values.size() > 0) ? values[0] : 0;
    pl.valueB = (values.size() > 1) ? values[1] : 0;
    pl.valueC = (values.size() > 2) ? values[2] : 0;
}

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
    for (int i = 0; i < _endpoints.size(); i++)
        _socket.send_to(boost::asio::buffer(vector), _endpoints[i]);
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