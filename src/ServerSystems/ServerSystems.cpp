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
    _lastUpdate = std::chrono::steady_clock::now();
}

rtp::ServerSystems::~ServerSystems()
{
}

void rtp::ServerSystems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += (vel.value().x * float(_timeElapsed) / 1000000 * 20);
            pos.value().y += (vel.value().y * float(_timeElapsed) / 1000000 * 20);
        }
    }
}

void rtp::ServerSystems::setEnemyRate(float seconds)
{
    _enemyRate = seconds;
}

void rtp::ServerSystems::spawnEnemies(eng::Registry &r)
{
    _enemyTimer -= float(_timeElapsed) / 1000000;

    if (_enemyTimer <= 0) {
        eng::Entity enm = r.spawnEntity();

        float posY = rand() % 1080;
        int scale = 3;

        r.addComponent<rtp::Position>(enm, rtp::Position(1919, posY, 0));
        r.addComponent<rtp::Velocity>(enm, rtp::Velocity(-5, 0));
        r.addComponent<rtp::EnemyStats>(enm, rtp::EnemyStats(5, 0));
        r.addComponent<rtp::RectCollider>(enm, rtp::RectCollider(40 * scale, 16 * scale));
        r.addComponent<rtp::Synced>(enm, rtp::Synced(enm.getId()));
        _enemyTimer = _enemyRate;
    }
}

// Max speed should be defined elsewhere...
void rtp::ServerSystems::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<Position>();
    auto &ves = r.getComponents<Velocity>();
    auto &pls = r.getComponents<PlayerStats>();
    float maxSpeed = 15;

    for (int i = 0; i < pos.size() && i < ves.size() && i < pls.size(); i++) {
        if (pos[i].has_value() && ves[i].has_value() && pls[i].has_value()) {
            auto &position = pos[i].value();
            auto &velocity = ves[i].value();
            auto &playerSt = pls[i].value();

            position.x = (position.x >= 1860) ? 1860 : position.x;
            position.x = (position.x < 0) ? 0 : position.x;
            position.y = (position.y >= 982) ? 982 : position.y;
            position.y = (position.y < 0) ? 0 : position.y;

            velocity.x = (velocity.x >= maxSpeed) ? maxSpeed : velocity.x;
            velocity.x = (velocity.x <= -maxSpeed) ? -maxSpeed : velocity.x;
            velocity.y = (velocity.y >= maxSpeed) ? maxSpeed : velocity.y;
            velocity.y = (velocity.y <= -maxSpeed) ? -maxSpeed : velocity.y;
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
            vel.value().x += ctrl.value().xAxis * (float(_timeElapsed) / 1000000 * 20 * 2);
            vel.value().x += (vel.value().x > 0) ? (float(_timeElapsed) / 1000000 * (-1)) * 20 : 0;
            vel.value().x += (vel.value().x < 0) ? (float(_timeElapsed) / 1000000 * 20) : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * (float(_timeElapsed) / 1000000) * 20 * 2;
            vel.value().y += (vel.value().y > 0) ? (float(_timeElapsed) / 1000000 * (-1)) * 20 : 0;
            vel.value().y += (vel.value().y < 0) ? (float(_timeElapsed) / 1000000) * 20 : 0;
        }
    }
}

void rtp::ServerSystems::controlFireSystem(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();
    auto &playerStats = r.getComponents<PlayerStats>();
    auto &positions = r.getComponents<Position>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value() && ctrl.value().shoot) {
            eng::Entity bullet = r.spawnEntity();
            auto &pos = positions[i].value();
            auto &plyr = playerStats[i].value();
            
            ctrl.value().shoot = false;
            ctrl.value().hasShot = true;
            r.addComponent(bullet, rtp::Velocity(15, 0));
            r.addComponent(bullet, rtp::Position(pos.x + 65, pos.y + 25, pos.z));
            r.addComponent(bullet, rtp::Bullet(2));
        }
    }
}

// Bullets are considered as (x, y) points
void rtp::ServerSystems::playerBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<Position>();

    for (int i = 0; i < blts.size() && i < poss.size(); i++) {
        if (blts[i].has_value() && poss[i].has_value()) {
            _bulletAgainstEnemy(r, eng::Entity(i));
        }
    }
}

void rtp::ServerSystems::_bulletAgainstEnemy(eng::Registry &r, eng::Entity blt)
{
    auto &enms = r.getComponents<EnemyStats>();
    auto &poss = r.getComponents<Position>();
    auto &rcts = r.getComponents<RectCollider>();
    auto &p = r.getComponents<Position>()[blt.getId()].value();
    auto &b = r.getComponents<Bullet>()[blt.getId()].value();

    for (int i = 0; i < enms.size() && i < poss.size() && i < rcts.size(); i++) {
        if (enms[i].has_value() && poss[i].has_value() && rcts[i].has_value()) {
            auto &enm = enms[i].value();
            auto &pos = poss[i].value();
            auto &rct = rcts[i].value();
            if (p.x >= pos.x && p.y >= pos.y) {
                if (p.x <= pos.x + rct.width && p.y <= pos.y + rct.height) {
                    enm.health -= b.damage;
                    r.killEntity(blt);
                }
            }
        }
    }
}

void rtp::ServerSystems::killDeadEnemies(eng::Registry &r)
{
    auto &ennemies = r.getComponents<EnemyStats>();

    for (int i = 0; i < ennemies.size(); i++)
        if (ennemies[i].has_value())
            if (ennemies[i].value().health <= 0)
                r.killEntity(eng::Entity(i));
}

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

    for (int i = 0; i < synceds.size(); i++)
        if (synceds[i].has_value() == true)
            if (synceds[i].value().id == syncId)
                return i;
    return -1;
}

void rtp::ServerSystems::limitTime()
{
    if ((_tps != 0) && ((1 / _tps) > _delta)) {
        long long sleeptime = ((1.0 / _tps) - _delta) * 1000000;
        std::this_thread::sleep_for(std::chrono::microseconds(sleeptime));       
        _timeElapsed = sleeptime + (_delta * 1000000);
    }
    else {
        _timeElapsed = _delta * 1000000;
    }
}

void rtp::ServerSystems::updDeltaTime()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    _delta = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
    _lastUpdate = now;
}

void rtp::ServerSystems::killOutOfBounds(eng::Registry &r)
{
    auto &poss = r.getComponents<Position>();

    for (int i = 0; i < poss.size(); i++) {
        if (poss[i].has_value()) {
            auto pos = poss[i].value();

            if (pos.x > 1920 || pos.x < -1)
                r.killEntity(eng::Entity(i));
            else if (pos.y > 1080 || pos.y < -1)
                r.killEntity(eng::Entity(i));
        }
    }
}