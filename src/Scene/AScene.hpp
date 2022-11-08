/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include "IScene.hpp"
#include "../Network/NetworkStructs.hpp"

namespace rtp
{
    struct scene_package_t {
        eng::Registry &reg;
        eng::GraphicSystems &graphic;
        eng::PhysicSystems &physic;
        eng::AudioSystems &audio;
        rtp::Network &network;
        eng::InputManager &input;
        eng::TextureManager &texture;
    };
    class AScene : public IScene {
    public:
        AScene(scene_package_t &pack);
        ~AScene() = default;
        void setupRegistry() override;
        void systemRun() override;
    protected:
        eng::Registry &_reg;
        eng::GraphicSystems &_graphic;
        eng::PhysicSystems &_physic;
        eng::AudioSystems &_audio;
        rtp::Network &_network;
        eng::InputManager &_input;
        eng::TextureManager &_texture;
    private:
};
} // namespace rtp

#endif /* !ASCENE_HPP_ */
