/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystem
*/

#include "ServerSystem.hpp"
#include "../GameComponent/Synced.hpp"
#include "../GameComponent/PlayerStats.hpp"
#include "../GameComponent/EnemyStats.hpp"
#include "../GameComponent/Controllable.hpp"
#include <cstdarg>

rtp::ServerSystem::ServerSystem(rtp::UDPServer &server): _udp(server)
{
}

rtp::ServerSystem::~ServerSystem()
{
}

static void addToPayload(std::vector<int> &data, int count, ...)
{
    std::va_list args;
    va_start(args, count);
    for (int i = 0; i < count; i++) {
        data.push_back(va_arg(args, int));
    }
    va_end(args);
}

void rtp::ServerSystem::sendData(eng::Registry &reg)
{
    std::vector<int> data;
    auto synceds = reg.getComponents<Synced>();
    auto pos = reg.getComponents<eng::Position>();
    auto vel = reg.getComponents<eng::Velocity>();
    auto pls = reg.getComponents<PlayerStats>();
    auto ens = reg.getComponents<EnemyStats>();

    data.push_back(25122000);   // payload header verif number
    data.push_back(0);          // payload header body size
    for (int i = 0; i < synceds.size(); i++) {
        if (!synceds[i].has_value())
            continue;
        data.push_back(14052002);   // synced entity header
        data.push_back(synceds[i].value().id);  // syncId
        if (i > pos.size() && pos[i].has_value()) {
            auto &value = pos[i].value();
            addToPayload(data, 5, position, value.x, value.y, value.z, value.rotation);
        }
        if (i < vel.size() && vel[i].has_value()) {
            auto &value = vel[i].value();
            addToPayload(data, 4, velocity, value.x, value.y, value.angular);
        }
        if (i < pls.size() && pls[i].has_value()) {
            auto &value = pls[i].value();
            addToPayload(data, 4, playerStats, value.damage, value.lives, value.score);
        }
        if (i < ens.size() && ens[i].has_value()) {
            auto &value = ens[i].value();
            addToPayload(data, 4, enemyStats, value.enemyType, value.health);
        }
    }
    data[1] = data.size() - 2;
    _udp.sendToAll(data);
}

/*
 payload client -> server
 
 header
 25122000
 syncId
 body
 xAxis:[-1;+1]
 yAxis:[-1;+1]
 shoot: 1/0
 missile: 1/0
*/

static int getSyncedEntity(eng::Registry &reg, int syncId)
{
    auto &synceds = reg.getComponents<rtp::Synced>();

    for (int i = 0; i < synceds.size(); i++) {
        if (synceds[i].has_value() && synceds[i].value().id == syncId) {
            return (i);
        }
    }
    return (-1);
}

void rtp::ServerSystem::receiveData(eng::Registry &reg)
{
    std::vector<int> data = _udp.receive();
    auto &synceds = reg.getComponents<Synced>();
    auto &ctrl = reg.getComponents<Controllable>();

    for (int i = 0; i < data.size(); i++) {
        if (data[i] != 25122000)
            continue;
        ctrl[i].value().xAxis = data[i + 1];
        ctrl[i].value().yAxis = data[i + 2];
        ctrl[i].value().shoot = data[i + 3];
        ctrl[i].value().canonShoot = data[i + 4];
    }
}