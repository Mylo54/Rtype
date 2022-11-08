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
#include "../Scene/AScene.hpp"
#include "../Scene/MainMenu.hpp"

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
        pause
        // ...others
    };

    class Client {
        public:
            Client();
            ~Client();

            /// @brief run the Client
            /// @return 0 on success, 84 on program failure
            int run();
            int connect(eng::RegistryManager &manager, bool multiplayer, int lvl, int map);
        protected:
        private:
            scene_package_t _makePackage();

            int _sceneEvent;
            int _sceneNumber;
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
