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
            // ctrl.value().xAxis = input.getActionStrength("ui_right") > 0.1f ? 1.0f : 0.0f;
            // ctrl.value().xAxis = input.getActionStrength("ui_left") > 0.1f ? -1.0f : ctrl.value().xAxis;
            // ctrl.value().yAxis = input.getActionStrength("ui_down") > 0.1f ? 1.0f : 0.0f;
            // ctrl.value().yAxis = input.getActionStrength("ui_up") > 0.1f ? -1.0f : ctrl.value().yAxis;

            ctrl.value().xAxis = input.getActionStrength("ui_right");
            ctrl.value().yAxis = input.getActionStrength("ui_up");
            // Move -button
            ctrl.value().xAxis -= input.getActionStrength("ui_left");
            ctrl.value().yAxis -= input.getActionStrength("ui_down");
            // // Shoot
            ctrl.value().shoot = input.isActionPressed("ui_fire");
            ctrl.value().canonShoot = input.isActionPressed("ui_missile");

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
            vel.value().y -= ctrl.value().yAxis * delta * 200 * 2;
        }
    }
}

void rtp::PlayerSystem::controlFireSystem(eng::Registry &reg, float delta)
{
    auto &shooters = reg.getComponents<rtp::Shooter>();
    auto &canons = reg.getComponents<rtp::Canon>();
    auto &controllables = reg.getComponents<rtp::Controllable>();

    for (int i = 0; i < controllables.size() && i < shooters.size(); i++) {
        auto &sht = shooters[i];
        auto &cnn = canons[i];
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
        if (cnn.has_value() && ctrl.has_value()) {
            if (cnn.value().nextFire > 0) {
                cnn.value().nextFire -= delta;
            }
            if (ctrl.value().canonShoot && cnn.value().nextFire <= 0)  {
                cnn.value().shoot = true;
                cnn.value().nextFire = cnn.value().fireRate / 1;
            }
        }
    }
}

void rtp::PlayerSystem::shootSystem(eng::Registry &reg)
{
    auto &positions = reg.getComponents<eng::Position>();
    auto &shooters = reg.getComponents<rtp::Shooter>();
    auto &canons = reg.getComponents<rtp::Canon>();

    for (int i = 0; i < positions.size() && i < shooters.size(); i++) {
        auto &pos = positions[i];
        auto &sht = shooters[i];
        auto &cnn = canons[i];
        
        if (pos.has_value() && sht.has_value()) {
            if (sht.value().shoot) {
                float x = pos.value().x + sht.value().shootPoint[0];
                float y = pos.value().y + sht.value().shootPoint[1];
                float z = pos.value().z;
                sht.value().shoot = false;
                eng::Entity bullet = reg.spawnEntity();
                reg.addComponent(bullet, eng::Velocity(sht.value().speed));
                reg.addComponent(bullet, eng::Position(x, y, z));
                reg.addComponent(bullet, eng::Drawable(sht.value().bulletSpritePath));
                reg.addComponent(bullet, eng::Sound("assets/fire.wav", true));
                reg.addComponent(bullet, rtp::Bullet(2));
            }
        }
        if (pos.has_value() && cnn.has_value()) {
            if (cnn.value().shoot) {
                float x = pos.value().x + cnn.value().shootPoint[0];
                float y = pos.value().y + cnn.value().shootPoint[1];
                float z = pos.value().z;
                cnn.value().shoot = false;
                eng::Entity bullet = reg.spawnEntity();
                reg.addComponent(bullet, eng::Velocity(cnn.value().speed));
                reg.addComponent(bullet, eng::Position(x, y, z));
                reg.addComponent(bullet, eng::Drawable(cnn.value().bulletSpritePath));
                reg.addComponent(bullet, eng::Sound("assets/fire.wav", true));
                reg.addComponent(bullet, rtp::Bullet(20));
            }
        }
    }
}

void rtp::PlayerSystem::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<eng::Position>();
    auto &ves = r.getComponents<eng::Velocity>();
    auto &pls = r.getComponents<PlayerStats>();

    for (int i = 0; i < pos.size() && i < ves.size() && i < pls.size(); i++) {
        if (pos[i].has_value() && ves[i].has_value() && pls[i].has_value()) {
            auto &position = pos[i].value();
            auto &velocity = ves[i].value();
            auto &playerSt = pls[i].value();

            position.x = (position.x >= 1860) ? 1860 : position.x;
            position.x = (position.x < 0) ? 0 : position.x;
            position.y = (position.y >= 982) ? 982 : position.y;
            position.y = (position.y < 0) ? 0 : position.y;
        }
    }
}
