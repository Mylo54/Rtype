/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** End
*/

#ifndef END_HPP_
#define END_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp {
    class End : public AScene {
        public:
            /// @brief End object constructor
            End(rtp::scene_package_t pack, bool win, int &score);
            ~End();
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:
            void _addResult();
            void _addScore();

            /// @brief Adds all buttons to the scene
            void _addButtons();

            /// @brief Adds button Exit to the scene
            void _addButtonExit();

            void _addButtonMainMenu();
            void _addButtonRestart();
            /// @brief Add layers of backgrounds to the scene
            void _addBackgrounds();

            /// @brief fct for button exit
            int _exitBtnFunction();
            int _mainMenuBtnFunction();
            int _restartBtnFunction();
        private:
            bool _win;
            int &_score;
    };
}

#endif /* !END_HPP_ */
