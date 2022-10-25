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
    auto &ps = r.getComponents<Position>();
    auto &vs = r.getComponents<Velocity>();
    auto &playerStats = r.getComponents<PlayerStats>();
    auto &enemyStats = r.getComponents<EnemyStats>();
    auto &bonus = r.getComponents<Bonus>();
    auto &sc = r.getComponents<Synced>();
    auto &ctrls = r.getComponents<Controllable>();
    boost::array<server_payload_t, 1> dataTbs;

    for (int i = 0; i < sc.size(); i++) {
        if (sc[i].has_value() && i < playerStats.size() && playerStats[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &id_sync = sc[i].value();
            auto &player = playerStats[i].value();
            auto &ctrl = ctrls[i].value();

            _editDataTbs(dataTbs[0], PLAYER_STATS, {(float)player.playerId, (float)player.damage, (float)player.lives}, id_sync.id, ctrl.hasShot);
            ctrl.hasShot = false;
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], POSITION, {p.x, p.y, p.z}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], VELOCITY, {v.x, v.y}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
        }
        if (sc[i].has_value() && i < enemyStats.size() && enemyStats[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &enm = enemyStats[i].value();
            auto &id_sync = sc[i].value();

            _editDataTbs(dataTbs[0], ENEMY_STATS, {(float)enm.enemyType, (float)enm.health}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], POSITION, {p.x, p.y, p.z}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], VELOCITY, {v.x, v.y}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
        }
        if (sc[i].has_value() && i < bonus.size() && bonus[i].has_value()) {
            auto &p = ps[i].value();
            auto &v = vs[i].value();
            auto &bns = bonus[i].value();
            auto &id_sync = sc[i].value();

            _editDataTbs(dataTbs[0], BONUS, {(float)bns.type}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], POSITION, {p.x, p.y, p.z}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
            _editDataTbs(dataTbs[0], VELOCITY, {v.x, v.y}, id_sync.id);
            sendSyncedDataToAll(dataTbs);
        }
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