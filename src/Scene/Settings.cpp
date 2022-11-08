/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Settings
*/

#include "Settings.hpp"

rtp::Settings::Settings(scene_package_t pack, sf::Color c): AScene(pack), color(c)
{
}

rtp::Settings::~Settings()
{
}

void rtp::Settings::setupRegistry()
{
    _reg.registerComponents(eng::SparseArray<eng::Velocity>());
    _reg.registerComponents(eng::SparseArray<eng::Position>());
    _reg.registerComponents(eng::SparseArray<eng::Drawable>());
    _reg.registerComponents(eng::SparseArray<eng::Sound>());
    _reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    _reg.registerComponents(eng::SparseArray<eng::Writable>());
    _reg.registerComponents(eng::SparseArray<eng::Music>());
    _reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    _reg.registerComponents(eng::SparseArray<eng::RigidBody>());
}

void rtp::Settings::systemRun()
{
    // Update input events
    _input.updateEvents();

    if (_input.isActionJustPressed("ui_escape"))
        _sceneEvent = 1;
    if (_input.isActionJustPressed("ui_accept")) {
        _sceneEvent = 2;
        _sceneNumber = 3;
    }

    // Play sounds & music
    _audio.playMusic(_reg);
    _audio.playSound(_reg);

    // clear, draw & display
    _graphic.clear(color);
    _graphic.animateSystem(_reg);
    _graphic.display();
    _graphic.particleSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.writeSystem(_reg);
}
