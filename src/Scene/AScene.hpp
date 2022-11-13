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
#include "../System/ButtonSystem.hpp"
#include "../System/PlayerSystem.hpp"
#include "../System/KillSystem.hpp"
#include "../System/BackgroundSystem.hpp"
#include "../System/EnemySystem.hpp"
#include "../System/TextSystem.hpp"

namespace rtp
{
    struct scene_package_t {
        eng::Registry &reg;
        eng::GraphicSystems &graphic;
        eng::PhysicSystems &physic;
        eng::AudioSystems &audio;
        // rtp::Network &network;
        eng::SuperInput &input;
        eng::TextureManager &texture;
        int &sceneEvent;
        int &sceneNumber;
        int &score;
        int &level;
    };
    class AScene : public IScene {
        public:
            AScene(scene_package_t pack);
            ~AScene() = default;
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:
            int &_sceneEvent;
            int &_sceneNumber;
            int &_score;
            int &_level;
            eng::Registry &_reg;
            eng::GraphicSystems &_graphic;
            eng::PhysicSystems &_physic;
            eng::AudioSystems &_audio;
            // rtp::Network &_network;
            eng::SuperInput &_input;
            eng::TextureManager &_texture;
            rtp::ButtonSystem _buttonSystem;
            rtp::PlayerSystem _playerSystem;
            rtp::KillSystem _killSystem;
            rtp::BackgroundSystem _backgroundSystem;
            rtp::EnemySystem _enemySystem;
            rtp::TextSystem _textSystem;
        private:
    };
} // namespace rtp

#endif /* !ASCENE_HPP_ */
