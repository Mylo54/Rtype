/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Credits
*/

#ifndef CREDITS_HPP_
#define CREDITS_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp {
    class Credits : public AScene {
        public:
            /// @brief Credits object constructor
            Credits(rtp::scene_package_t pack);
            ~Credits();
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:
            void _addTitle();
            void _addTeamText();

            /// @brief Adds all buttons to the scene
            void _addButtons();

            void _addButtonMainMenu();
            /// @brief Add layers of backgrounds to the scene
            void _addBackgrounds();

            int _mainMenuBtnFunction();
        private:
    };
}

#endif /* !CREDITS_HPP_ */
