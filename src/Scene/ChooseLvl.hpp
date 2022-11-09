/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ChooseLvl
*/

#ifndef CHOOSELEVEL_HPP_
#define CHOOSELEVEL_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp {
    class ChooseLvl : public AScene {
        public:
            /// @brief ChooseLvl object constructor
            ChooseLvl(rtp::scene_package_t pack);
            ~ChooseLvl();
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:

            /// @brief Adds all buttons to the scene
            void _addButtons();
            /// @brief Add layers of backgrounds to the scene
            void _addBackgrounds();
            
            void _addButtonLvl1();
            /// @brief Adds button level 2 selection to a registry
            void _addButtonLvl2();
            /// @brief Adds button level 3 selection to a registry
            void _addButtonLvl3();
            /// @brief Adds button level 4 selection to a registry
            void _addButtonLvl4();
            /// @brief Adds button level final selection to a registry
            void _addButtonLvlFinal();

            /// @brief fct for button level 1
            int _btnFctlvl1();
            /// @brief fct for button level 2
            int _btnFctlvl2();
            /// @brief fct for button level 3
            int _btnFctlvl3();
            /// @brief fct for button level 4
            int _btnFctlvl4();
            /// @brief fct for button final level
            int _btnFctlvlB();
        private:
    };
}

#endif /* !CHOOSELEVEL_HPP_ */
