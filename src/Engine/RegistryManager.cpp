/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** RegistryManager
*/

#include "RegistryManager.hpp"

eng::RegistryManager::RegistryManager()
{
}

eng::RegistryManager::~RegistryManager()
{
}

void eng::RegistryManager::addRegistry(eng::Registry &reg)
{
    reg.setDebugMode(this->getDebugMode());
    reg.setLogPath(this->getLogPath());
    _regs.push(reg);
}

void eng::RegistryManager::popRegistry()
{
    _regs.pop();
}

// Seems to crash
eng::Registry &eng::RegistryManager::getTop()
{
    try {
        return _regs.top();
    }
    catch (const std::exception e) {
        std::cerr << e.what();
    }
}

std::stack<eng::Registry> &eng::RegistryManager::getRegistries()
{
    return _regs;
}

void eng::RegistryManager::setDebugMode(bool isEnable)
{
    _debugMode = isEnable;
}

bool eng::RegistryManager::getDebugMode()
{
    return _debugMode;
}

void eng::RegistryManager::setLogPath(std::string path)
{
    _logPath = path;
}

std::string eng::RegistryManager::getLogPath()
{
    return _logPath;
}