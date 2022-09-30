/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** Registry
*/

#include "Registry.hpp"

eng::Registry::Registry()
{
}

eng::Registry::~Registry()
{
}

void eng::Registry::setDebugMode(bool isEnable)
{
    _debugMode = isEnable;
}

bool eng::Registry::getDebugMode()
{
    return _debugMode;
}