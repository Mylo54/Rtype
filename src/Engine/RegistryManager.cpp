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

void eng::RegistryManager::addRegistry(std::string name)
{
    eng::Registry reg;
    eng::SparseArray<rtp::Position> position;
    eng::SparseArray<rtp::Velocity> velocity;
    eng::SparseArray<rtp::Drawable> drawable;
    eng::SparseArray<rtp::Controllable> control;
    eng::SparseArray<rtp::Shooter> shooter;
    eng::SparseArray<rtp::Background> backgrounds;
    eng::SparseArray<rtp::AudioSource> sounds;

    reg.setName(name);
    reg.setDebugMode(this->getDebugMode());
    reg.setLogPath(this->getLogPath());
    reg.registerComponents(position);
    reg.registerComponents(velocity);
    reg.registerComponents(drawable);
    reg.registerComponents(control);
    reg.registerComponents(shooter);
    reg.registerComponents(backgrounds);
    reg.registerComponents(sounds);

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