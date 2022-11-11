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
            // ctrl.value().shoot = input.isActionPressed("Fire");

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
            vel.value().x += ctrl.value().xAxis * delta * 20 * 2;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * delta * 20 * 2;
        }
    }
}

// // Max speed should be defined elsewhere...
// void rtp::PlayerSystem::limitPlayer(eng::Registry &r)
// {
//     auto &pos = r.getComponents<eng::Position>();
//     auto &ves = r.getComponents<eng::Velocity>();
//     float maxSpeed = 15;

//     for (int i = 0; i < pos.size() && i < ves.size(); i++) {
//         if (pos[i].has_value() && ves[i].has_value()) {
//             auto &position = pos[i].value();
//             auto &velocity = ves[i].value();

//             position.x = (position.x >= 1860) ? 1860 : position.x;
//             position.x = (position.x < 0) ? 0 : position.x;
//             position.y = (position.y >= 982) ? 982 : position.y;
//             position.y = (position.y < 0) ? 0 : position.y;

//             velocity.x = (velocity.x >= maxSpeed) ? maxSpeed : velocity.x;
//             velocity.x = (velocity.x <= -maxSpeed) ? -maxSpeed : velocity.x;
//             velocity.y = (velocity.y >= maxSpeed) ? maxSpeed : velocity.y;
//             velocity.y = (velocity.y <= -maxSpeed) ? -maxSpeed : velocity.y;
//         }
//     }
// }