/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TimeSystems
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::limitTime()
{
    if ((_tps != 0) && ((1 / _tps) > _elapsedTime)) {
        long long sleeptime = ((1.0 / _tps) - _elapsedTime) * 1000000;
        std::this_thread::sleep_for(std::chrono::microseconds(sleeptime));       
        _delta = sleeptime + (_elapsedTime * 1000000);
    }
    else {
        _delta = _elapsedTime * 1000000;
    }
}

void rtp::ServerSystems::updDeltaTime()
{
    std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    _elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(now - _lastUpdate).count() / 1000000.0f;
    _lastUpdate = now;
}

float rtp::ServerSystems::_getDeltaAsSeconds()
{
    return (float(_delta) / 1000000);
}
