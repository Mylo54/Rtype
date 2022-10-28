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
        private:
            eng::RegistryManager &_manager;
            std::function<int(eng::RegistryManager &)> _singlePlayerBtnFct;
    };
}

#endif /* !CHOOSELVL_HPP_ */
