/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp
{
    class Settings : public AScene {
        public:
            Settings(scene_package_t pack);
            ~Settings();

            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;

            /// @brief Add all elements in the settings scene
            void addElements();
            void addBackgrounds();
        protected:
            void _addTitle();
            void _addMusic();
            void _addSfx();

            void _addFrameRateButton();
            void _addFrameRateText();
            int _frameRateBtnFunction();

            void _addMusicButton();
            void _addMusicText();
            int _musicBtnFunction();

            void _addSfxButton();
            void _addSfxText();
            int _sfxBtnFunction();
            void _soundTest();
        private:
    };
} // namespace rtp

#endif /* !SETTINGS_HPP_ */
