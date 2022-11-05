/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TimeSystems
*/

#include "ServerSystems.hpp"

void rtp::ServerSystems::limitTickRate()
{
    if (_tps != 0) {
        float elapsed = (std::clock() - _lastClockTime) / CLOCKS_PER_SEC;
        usleep((_tps - elapsed) * CLOCKS_PER_SEC);
        _delta = _tps - elapsed;
        _lastClockTime = std::clock();
    }
}

float &rtp::ServerSystems::getDelta()
{
    return _delta;
}

void rtp::ServerSystems::setTickRate(unsigned int tps)
{
    if (tps == 0)
        _tps = 0;
    else
        _tps = 1.0f / tps;
}