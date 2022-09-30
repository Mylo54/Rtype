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

void eng::Registry::log(std::string log)
{
    time_t now = time(0);
    tm* ltm = localtime(&now);

    std::cout << ltm->tm_mday << "/";
    std::cout << 1 + ltm->tm_mon << "/";
    std::cout << 1900 + ltm->tm_year << " | " ;
    std::cout<< 5 + ltm->tm_hour << ":";
    std::cout << 30 + ltm->tm_min << ":";
    std::cout << ltm->tm_sec << " | " ;
    std::cout << log << std::endl;
}

void eng::Registry::setName(std::string name)
{
    _name = name;
}

std::string eng::Registry::getName()
{
    return _name;
}