/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** AScene
*/

#ifndef ASCENE_HPP_
#define ASCENE_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "IScene.hpp"
#include "../Network/Network.hpp"

namespace rtp
{
    struct scene_package_t {
        eng::Registry &reg;
        eng::GraphicSystems &graphic;
        eng::PhysicSystems &physic;
        eng::AudioSystems &audio;
        rtp::Network &network;
        eng::SuperInput &input;
        eng::TextureManager &texture;
        int &sceneEvent;
        int &sceneNumber;
    };
    class AScene : public IScene {
    public:
        AScene(scene_package_t pack);
        ~AScene() = default;
        void setupRegistry() override;
        void systemRun() override;
    protected:
        int &_sceneEvent;
        int &_sceneNumber;
        eng::Registry &_reg;
        eng::GraphicSystems &_graphic;
        eng::PhysicSystems &_physic;
        eng::AudioSystems &_audio;
        rtp::Network &_network;
        eng::SuperInput &_input;
        eng::TextureManager &_texture;
    private:
};
} // namespace rtp

#endif /* !ASCENE_HPP_ */
