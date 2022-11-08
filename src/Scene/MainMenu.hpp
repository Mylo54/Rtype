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
#include <memory>
#include "AScene.hpp"

namespace rtp {
    class MainMenu : public AScene {
        public:

            /// @brief MainMenu object constructor
            /// @param manager reference to registry manager
            /// @param co function connect
            MainMenu(rtp::scene_package_t pack);
            ~MainMenu();
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:

            /// @brief Adds all buttons to the scene
            void _addButtons();

            /// @brief Adds button singleplayer to the scene
            void _addButtonStartLocal();

            /// @brief Adds button Exit to the scene
            void _addButtonExit();

            /// @brief Adds button multiplayer to the scene
            void _addButtonMultiplayer();

            /// @brief Adds button Setting to the scene
            void _addButtonSettings();

            /// @brief Add layers of backgrounds to the scene
            void _addBackgrounds();

            /// @brief Add sprite earth to the scene
            void _addEarth();

            /// @brief fct for button exit
            /// @param reg The RegistryManager
            int _exitBtn(eng::RegistryManager &regMan);

            /// @brief fct for button choose lvl
            /// @param regMan The RegistryManager
            int _chooseLvlBtn(eng::RegistryManager &regMan);

            /// @brief fct for button multiplayer
            /// @param regMan The RegistryManager
            int _MultiBtn(eng::RegistryManager &regMan);

        private:
            /// @brief fct which is used in btn to connect to the server
            // std::function<int(eng::RegistryManager &, bool, int, int)> &_singlePlayerBtnFct;
    };
}

#endif /* !MAINMENU_HPP_ */
