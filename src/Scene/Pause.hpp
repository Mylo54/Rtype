/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** Pause
*/

#ifndef PAUSE_HPP_
#define PAUSE_HPP_

#include "AScene.hpp"

namespace rtp {
    class Pause : public AScene {
        public:
            Pause(rtp::scene_package_t pack);
            ~Pause();

            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
        protected:
            /// @brief Adds all buttons to the scene
            void _addButtons();

            /// @brief Adds button Resume to the scene
            void _addResumeButton();

            /// @brief Adds button Settings to the scene
            void _addSettingsButton();

            /// @brief Adds button MainMenu to the scene
            void _addMainMenuButton();

            /// @brief Adds button Setting to the scene
            //void _addButtonSettings();

            /// @brief Add layers of backgrounds to the scene
            void _addBackgrounds();

            /// @brief Add sprite earth to the scene
            //void _addEarth();

            /// @brief fct for button exit
            //int _exitBtn();

            /// @brief fct for button Resume
            int _resumeBtn();

            /// @brief fct for button MainMenu
            int _mainMenuBtn();

            /// @brief fct for button Settings
            int _settingsBtn();
        private:
    };
}

#endif /* !PAUSE_HPP_ */
