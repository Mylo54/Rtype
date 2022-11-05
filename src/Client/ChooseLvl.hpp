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
#include "../ClientSystems/NetworkSystems.hpp"
#include "../NetworkStructs.hpp"
#include "Miscellaneous.hpp"

namespace rtp {
    class ChooseLvl {
        public:
            ChooseLvl(eng::RegistryManager &manager,
            std::function<int(eng::RegistryManager &, bool, int)> &co,
            eng::TextureManager &textureManager);
            ~ChooseLvl();

        protected:

            /// @brief Adds all buttons to a registry
            /// @param reg The Registry on which to adds the buttons
            void _addButtons(eng::Registry &r);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds(eng::Registry &reg);

            /// @brief Adds button level 1 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonLvl1(eng::Registry &r);

            /// @brief Adds button level 2 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonLvl2(eng::Registry &r);

            /// @brief Adds button level 3 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonLvl3(eng::Registry &r);

            /// @brief Adds button level 4 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonLvl4(eng::Registry &r);

            /// @brief Adds button level final selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonLvlFinal(eng::Registry &r);

            /// @brief fct for button level 1
            /// @param reg The RegistryManager
            int _btnFctlvl1(eng::RegistryManager &reg);

            /// @brief fct for button level 2
            /// @param reg The RegistryManager
            int _btnFctlvl2(eng::RegistryManager &reg);

            /// @brief fct for button level 3
            /// @param reg The RegistryManager
            int _btnFctlvl3(eng::RegistryManager &reg);

            /// @brief fct for button level 4
            /// @param reg The RegistryManager
            int _btnFctlvl4(eng::RegistryManager &reg);

            /// @brief fct for button final level
            /// @param reg The RegistryManager
            int _btnFctlvlB(eng::RegistryManager &reg);

        private:
            eng::RegistryManager &_manager;
            eng::TextureManager &_textureManager;
            std::function<int(eng::RegistryManager &, bool, int)> &_singlePlayerBtnFct;
    };
}

#endif /* !CHOOSELVL_HPP_ */
