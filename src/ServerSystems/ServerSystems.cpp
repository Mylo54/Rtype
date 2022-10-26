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
            pos.value().x += (vel.value().x * float(_delta) / 1000000 * 20);
            pos.value().y += (vel.value().y * float(_delta) / 1000000 * 20);
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
            vel.value().x += ctrl.value().xAxis * _getDeltaAsSeconds() * 20 * 2;
            vel.value().x += (vel.value().x > 0) ? -(_getDeltaAsSeconds() * 20) : 0;
            vel.value().x += (vel.value().x < 0) ? _getDeltaAsSeconds() * 20 : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * _getDeltaAsSeconds() * 20 * 2;
            vel.value().y += (vel.value().y > 0) ? -(_getDeltaAsSeconds() * 20) : 0;
            vel.value().y += (vel.value().y < 0) ? _getDeltaAsSeconds() * 20 : 0;
        }
    }
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

void rtp::ServerSystems::collisions(eng::Registry &r)
{
    bonusCollisions(r);
    enemyCollisions(r);
}