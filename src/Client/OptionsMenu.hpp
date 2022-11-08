/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** OptionsMenu
*/

#ifndef OPTIONSMENU_HPP_
#define OPTIONSMENU_HPP_

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
    class OptionsMenu {
        public:
            OptionsMenu(eng::RegistryManager &manager, eng::GraphicSystems &gfx,
            eng::TextureManager &textureManager);
            ~OptionsMenu();

        protected:
            //void _setupRegistry(eng::Registry &reg);
            void _addButton(eng::Registry &r);
            void _addBackground(eng::Registry &reg);
            void _addMainMenuButton(eng::Registry &r);
            void _addExitButton(eng::Registry &r);
            //void _addSettingsButton(eng::Registry &r);
            //void _addResumeButton(eng::Registry &r);
            //int _exitBtn(eng::RegistryManager &reg);
        private:
            eng::RegistryManager &_manager;
            eng::GraphicSystems &_gfx;
            eng::TextureManager &_textureManager;
    };
}

#endif /* !OPTIONSMENU_HPP_ */
