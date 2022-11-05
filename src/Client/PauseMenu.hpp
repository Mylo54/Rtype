/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** PauseMenu
*/

#ifndef PAUSEMENU_HPP_
#define PAUSEMENU_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Components/Components.hpp"
#include "../ClientSystems/ClientSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include "../NetworkStructs.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"

namespace rtp {
    class PauseMenu {
        public:
            PauseMenu(eng::RegistryManager &manager, eng::GraphicSystems &gfx,
            eng::TextureManager &textureManager);
            ~PauseMenu();

        protected:
            void _addButton(eng::Registry &r);
            void _addResumeButton(eng::Registry &r);
            void _addSettingsButton(eng::Registry &r);
            void _addMainMenuButton(eng::Registry &r);
            void _addExitButton(eng::Registry &r);
            void _addBackgrounds(eng::Registry &reg);
            int _exitBtn(eng::RegistryManager &reg);
        private:
            eng::RegistryManager &_manager;
            std::function<int(eng::RegistryManager &)> _gameBtnFct;
            eng::GraphicSystems &_gfx;
            eng::TextureManager &_textureManager;
    };
}

#endif /* !PAUSEMENU_HPP_ */
