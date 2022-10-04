/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** Engine
*/

#include "Engine.hpp"

eng::Engine::Engine()
{
}

eng::Engine::~Engine()
{
}

void eng::Engine::addRegistry(eng::Registry &reg)
{
    _regs.push(reg);
}

void eng::Engine::popRegistry()
{
    _regs.pop();
}

eng::Registry &eng::Engine::getRegistry(std::string regName)
{
    std::stack<eng::Registry> regcopy = _regs;

    while(!regcopy.empty()) {
        if (regcopy.top().getName() == regName) return regcopy.top();
    }
    throw std::invalid_argument("getRegistry error : registry not found.");
}

std::stack<eng::Registry> &eng::Engine::getRegistries()
{
    return _regs;
}
