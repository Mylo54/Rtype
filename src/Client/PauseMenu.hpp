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
#include "../ClientSystems/GraphicsSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include "../NetworkStructs.hpp"
#include "Game.hpp"

namespace rtp {
    class PauseMenu {
        public:
            PauseMenu(eng::RegistryManager &manager);
            ~PauseMenu();

        protected:
            void _addButton(eng::Registry &r);
            void _setupRegistry(eng::Registry &reg);
            void _addResumeButton(eng::Registry &r);
            void _addSettingsButton(eng::Registry &r);
            void _addMainMenuButton(eng::Registry &r);
            void _addExitButton(eng::Registry &r);
        private:
            eng::RegistryManager &_manager;
            std::function<int(eng::RegistryManager &)> _singlePlayerBtnFct;
    };
}

#endif /* !PAUSEMENU_HPP_ */
