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

void eng::Registry::setName(std::string name)
{
    _name = name;
}

std::string eng::Registry::getName()
{
    return _name;
}

void eng::Registry::setLogPath(std::string path)
{
    _log.setPath(path);
}

std::string eng::Registry::getLogPath()
{
    return _log.getPath();
}