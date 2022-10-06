/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** RegistryManager
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "RegistryManager.hpp"

eng::RegistryManager::RegistryManager()
{
}

eng::RegistryManager::~RegistryManager()
{
}

void eng::RegistryManager::addRegistry(std::string name)
{
    eng::Registry reg;
    
    reg.setName(name);
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

void eng::RegistryManager::createLogPath()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    std::stringstream path;
    path << (ltm->tm_mday) << "-" <<
    (1 + ltm->tm_mon) << "-" << (1900 + ltm->tm_year) << "_"
    << (5 + ltm->tm_hour) << "h" << (ltm->tm_min) << "m" << (ltm->tm_sec)
    << "s.log";
    
    std::ofstream out(path.str());
    out << "Log from this run:\n";
    out.close();
    this->_logPath = path.str();
}