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
#include "Game.hpp"

namespace rtp {
    class MainMenu {
        public:
            MainMenu(eng::RegistryManager &manager);
            ~MainMenu();

        protected:
            void _btnFuncStart(void);
            void _btnFuncExit(void);
            void _addButton(eng::Registry &reg);
            void _setupRegistry(eng::Registry &reg);
        private:
            eng::RegistryManager &_manager;
    };
}

#endif /* !MAINMENU_HPP_ */
