/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <stack>
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Network/Network.hpp"
#include "../Scene/Settings.hpp"

namespace rtp
{
    enum sceneEvent{
        none,
        popScene,
        pushScene,
    };

    enum sceneNumber{
        game,
        menu,
        pause,
        option
        // ...others
    };

    class Client {
        public:
            Client();
            ~Client();

            /// @brief run the Client
            /// @return 0 on success, 84 on program failure
            int run();
        protected:
        private:
            scene_package_t _makePackage();
            void _setupInputEvents();

            int _sceneEvent = sceneEvent::none;
            int _sceneNumber = sceneNumber::menu;
            eng::RegistryManager _registries;
            eng::SuperInput _inputs;
            eng::PhysicSystems _physics;
            eng::GraphicSystems _graphics;
            eng::AudioSystems _audio;
            rtp::Network _net;
            eng::TextureManager _textures;
            std::stack<rtp::IScene*> _scenes;
    };
} // namespace rtp



#endif /* !CLIENT_HPP_ */
