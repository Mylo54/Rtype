/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ChooseLvl
*/

#ifndef CHOOSELVL_HPP_
#define CHOOSELVL_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include <iostream>
#include <fstream>
#include "../Components/Components.hpp"
#include "../ClientSystems/ClientSystems.hpp"
#include "../ClientSystems/GraphicsSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include "../NetworkStructs.hpp"

namespace rtp {
    class ChooseLvl {
        public:
            ChooseLvl(eng::RegistryManager &manager, std::function<int(eng::RegistryManager &)> _singlePlayerBtnFct);
            ~ChooseLvl();

        protected:
            void _addButtons(eng::Registry &r);
            void _addButtonLvl1(eng::Registry &r);
            void _addButtonLvl2(eng::Registry &r);
            void _addButtonLvl3(eng::Registry &r);
            void _addButtonLvl4(eng::Registry &r);
            void _addButtonLvlFinal(eng::Registry &r);
            void _setupRegistry(eng::Registry &reg);
            void _addBackgrounds(eng::Registry &reg);

            int _btnFctlvl1(eng::RegistryManager &reg);
            int _btnFctlvl2(eng::RegistryManager &reg);
            int _btnFctlvl3(eng::RegistryManager &reg);
            int _btnFctlvl4(eng::RegistryManager &reg);
            int _btnFctlvlB(eng::RegistryManager &reg);
        private:
            eng::RegistryManager &_manager;
            std::function<int(eng::RegistryManager &)> _singlePlayerBtnFct;
    };
}

#endif /* !CHOOSELVL_HPP_ */
