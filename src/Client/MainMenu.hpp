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
#include "../Components/Components.hpp"
#include "../ClientSystems/ClientSystems.hpp"
#include "../ClientSystems/GraphicsSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../NetworkStructs.hpp"
#include "ChooseLvl.hpp"

namespace rtp {
    class MainMenu {
        public:

            /// @brief MainMenu object constructor
            /// @param manager reference to registry manager
            /// @param co function connect
            MainMenu(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&)> co, eng::GraphicSystems &gfx);
            ~MainMenu();

        protected:

            /// @brief Setup the registry with every sparse array needed
            /// @param reg The Registry to setup
            void _setupRegistry(eng::Registry &reg);

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

            int _exitBtn(eng::RegistryManager &reg);
            int _chooseLvlBtn(eng::RegistryManager &reg);
            int _MultiBtn(eng::RegistryManager &reg);

        private:
            eng::RegistryManager &_manager;
            
            /// @brief fct which is used in btn to connect to the server
            std::function<int(eng::RegistryManager &)> _singlePlayerBtnFct;
            eng::GraphicSystems &_gfx;
    };
}

#endif /* !MAINMENU_HPP_ */
