/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** PlayerSystem
*/

#include "PlayerSystem.hpp"

rtp::PlayerSystem::PlayerSystem()
{
}

rtp::PlayerSystem::~PlayerSystem()
{
}

void rtp::PlayerSystem::control(eng::Registry &reg, eng::SuperInput &input)
{
    auto &controllables = reg.getComponents<rtp::Controllable>();
    bool press = true;

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            // Move analog & button (round to integer because )
            ctrl.value().xAxis = input.getActionStrength("Move x") > 0.1f ? 1.0f : 0.0f;
            ctrl.value().xAxis = input.getActionStrength("Move x") < -0.1f ? -1.0f : ctrl.value().xAxis;
            ctrl.value().yAxis = input.getActionStrength("Move y")> 0.1f ? 1.0f : 0.0f;
            ctrl.value().yAxis = input.getActionStrength("Move y") < -0.1f ? -1.0f : ctrl.value().yAxis;

            // Move -button
            ctrl.value().xAxis -= input.getActionStrength("Move -x");
            ctrl.value().yAxis -= input.getActionStrength("Move -y");
            // Shoot
            ctrl.value().shoot = input.isActionPressed("Fire");
        }
    }
}