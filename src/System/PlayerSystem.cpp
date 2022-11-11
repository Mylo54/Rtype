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
            ctrl.value().xAxis = input.getActionStrength("ui_right") > 0.1f ? 1.0f : 0.0f;
            ctrl.value().xAxis = input.getActionStrength("ui_left") > 0.1f ? -1.0f : ctrl.value().xAxis;
            ctrl.value().yAxis = input.getActionStrength("ui_down") > 0.1f ? 1.0f : 0.0f;
            ctrl.value().yAxis = input.getActionStrength("ui_up") > 0.1f ? -1.0f : ctrl.value().yAxis;

            // Move -button
            // ctrl.value().xAxis -= input.getActionStrength("ui_left");
            // ctrl.value().yAxis -= input.getActionStrength("ui_up");
            // // Shoot
            ctrl.value().shoot = input.isActionPressed("ui_fire");

            // ctrl.value().yAxis = input.isActionPressed("ui_up") ? -1.0f : ctrl.value().yAxis;
            // ctrl.value().yAxis = input.isActionPressed("ui_up") ? -1.0f : 0.0f;
        }
    }   
}

void rtp::PlayerSystem::controlMovement(eng::Registry &reg, eng::SuperInput &input, float delta)
{
    auto &velocities = reg.getComponents<eng::Velocity>();
    auto &controllables = reg.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * delta * 200 * 2;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * delta * 200 * 2;
        }
    }
}

void rtp::PlayerSystem::controlFireSystem(eng::Registry &reg, float delta)
{
    auto &shooters = reg.getComponents<Shooter>();
    auto &controllables = reg.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < shooters.size(); i++) {
        auto &sht = shooters[i];
        auto &ctrl = controllables[i];

        if (sht.has_value() && ctrl.has_value()) {
            if (sht.value().nextFire > 0) {
                sht.value().nextFire -= delta;
            }
            if (ctrl.value().shoot && sht.value().nextFire <= 0)  {
                sht.value().shoot = true;
                sht.value().nextFire = sht.value().fireRate / 1;
            }
        }
    }
}