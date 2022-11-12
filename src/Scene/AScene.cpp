/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** AScene
*/

#include "AScene.hpp"

rtp::AScene::AScene(scene_package_t pack) : IScene(), _reg(pack.reg),
_graphic(pack.graphic), _physic(pack.physic), _audio(pack.audio),
_input(pack.input), _texture(pack.texture),
_sceneEvent(pack.sceneEvent), _sceneNumber(pack.sceneNumber)
{
}

void rtp::AScene::setupScene()
{
    setupRegistry();
}

void rtp::AScene::setupRegistry()
{
    _reg.registerComponents(eng::SparseArray<eng::Velocity>());
    _reg.registerComponents(eng::SparseArray<eng::Position>());
    _reg.registerComponents(eng::SparseArray<eng::Drawable>());
    _reg.registerComponents(eng::SparseArray<eng::Sound>());
    _reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    _reg.registerComponents(eng::SparseArray<eng::Writable>());
    _reg.registerComponents(eng::SparseArray<rtp::Button>());
    _reg.registerComponents(eng::SparseArray<eng::Music>());
    _reg.registerComponents(eng::SparseArray<eng::ParticleEmitter>());
    _reg.registerComponents(eng::SparseArray<eng::RigidBody>());
    _reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    _reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    _reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    _reg.registerComponents(eng::SparseArray<rtp::Canon>());
    _reg.registerComponents(eng::SparseArray<rtp::Background>());
    _reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    // _reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    // _reg.registerComponents(eng::SparseArray<rtp::Synced>());
    // _reg.registerComponents(eng::SparseArray<rtp::Bonus>());
}

void rtp::AScene::systemRun()
{
    _input.updateEvents();
    _graphic.clear();
    _graphic.animateSystem(_reg);
    _graphic.drawSystem(_reg);
    _graphic.display();
}