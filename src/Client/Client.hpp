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
#include "../System/ButtonSystem.hpp"
#include "../Scene/AScene.hpp"
#include "../Scene/Settings.hpp"
#include "../Scene/MainMenu.hpp"
#include "../Scene/Pause.hpp"
#include "../Scene/ChooseLvl.hpp"
#include "../Scene/Game.hpp"
#include "../Scene/WaitingRoom.hpp"
#include "../Scene/End.hpp"
#include "../Scene/Credits.hpp"

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
        option,
        chooseLvl,
        waiting,
        win,
        loose,
        credits
        // ...others
    };

    class Client {
        public:
            Client();
            ~Client();

            /// @brief Run the Client
            /// @return 0 on success, 84 on program failure
            int run();
            int connect(eng::RegistryManager &manager, bool multiplayer, int lvl, int map);
        protected:
        private:
            /// @brief Create a package with all necessity for AScene constructor
            /// @return The package
            scene_package_t _makePackage();
            /// @brief Set the inputEvent and action associated
            /// If you want to add an action :
            /// _inputs.addAction("action_name");
            /// _inputs.addEvent("action_name", eng::SuperInput::AssociatedInput);
            void _setupInputEvents();
            /// @brief A function handling scene events : poping or pushing specific scene
            void _handleSceneEvents();

            int _sceneEvent = sceneEvent::none;
            int _sceneNumber = sceneNumber::menu;
            eng::RegistryManager _registries;
            eng::SuperInput _inputs;
            eng::PhysicSystems _physics;
            eng::GraphicSystems _graphics;
            eng::AudioSystems _audio;
            // rtp::Network _net;
            eng::TextureManager _textures;
            rtp::ButtonSystem _buttonSystem;
            eng::SceneManager _sceneManager;
            std::stack<rtp::IScene*> _scenes;

    };
} // namespace rtp



#endif /* !CLIENT_HPP_ */
