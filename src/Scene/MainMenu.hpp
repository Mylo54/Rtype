/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
#define MAINMENU_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
// #include "../Components/Components.hpp"
// #include "../ClientSystems/ClientSystems.hpp"
// #include "../ClientSystems/NetworkSystems.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
// #include "../NetworkStructs.hpp"
// #include "ChooseLvl.hpp"
#include <memory>
// #include "Miscellaneous.hpp"
// #include "MapVoter.hpp"
#include "IScene.hpp"

namespace rtp {
    class MainMenu {
        public:

            /// @brief MainMenu object constructor
            /// @param manager reference to registry manager
            /// @param co function connect
            MainMenu(eng::RegistryManager &manager,
            std::function<int(eng::RegistryManager&, bool, int, int)> &co,
            eng::GraphicSystems &gfx, eng::TextureManager &textureManager);

            ~MainMenu();

        protected:

            /// @brief Adds all buttons to a registry
            /// @param reg The Registry on which to adds the buttons
            void _addButtons(eng::Registry &reg);

            /// @brief Adds button singleplayer to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonStartLocal(eng::Registry &reg);

            /// @brief Adds button Exit to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonExit(eng::Registry &reg);

            /// @brief Adds button multiplayer to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonMultiplayer(eng::Registry &reg);

            /// @brief Adds button Setting to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonSettings(eng::Registry &reg);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds(eng::Registry &reg);

            /// @brief Add sprite earth
            /// @param reg The Registry on which to add the sprite
            void _addEarth(eng::Registry &reg);

            /// @brief fct for button exit
            /// @param reg The RegistryManager
            int _exitBtn(eng::RegistryManager &reg);

            /// @brief fct for button choose lvl
            /// @param reg The RegistryManager
            int _chooseLvlBtn(eng::RegistryManager &reg);

            /// @brief fct for button multiplayer
            /// @param reg The RegistryManager
            int _MultiBtn(eng::RegistryManager &reg);

        private:
            eng::RegistryManager &_manager;
            
            /// @brief fct which is used in btn to connect to the server
            std::function<int(eng::RegistryManager &, bool, int, int)> &_singlePlayerBtnFct;
            eng::GraphicSystems &_gfx;
            eng::TextureManager &_textureManager;
    };
}

#endif /* !MAINMENU_HPP_ */
