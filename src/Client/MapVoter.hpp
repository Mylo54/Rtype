/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** MapVoter
*/

#ifndef MAPVOTER_HPP_
#define MAPVOTER_HPP_

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
#include <memory>

namespace rtp {
    class MapVoter {
        public:
            /// @brief MapVoter object constructor
            /// @param manager reference to registry manager
            /// @param co function connect
            MapVoter(eng::RegistryManager &manager, std::function<int(eng::RegistryManager&, bool, int, int)> &co);
            ~MapVoter();

        protected:
            /// @brief Setup the registry with every sparse array needed
            /// @param reg The Registry to setup
            void _setupRegistry(eng::Registry &reg);

            /// @brief Adds all buttons to a registry
            /// @param reg The Registry on which to adds the buttons
            void _addButtons(eng::Registry &reg);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds(eng::Registry &reg);

            /// @brief Adds button map 1 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonMap1(eng::Registry &r);

            /// @brief Adds button map 2 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonMap2(eng::Registry &r);

            /// @brief Adds button map 3 selection to a registry
            /// @param reg The Registry on which to adds the button
            void _addButtonMap3(eng::Registry &r);

            /// @brief fct for button map 1
            /// @param reg The RegistryManager
            int _btnFctMap1(eng::RegistryManager &reg);

            /// @brief fct for button map 2
            /// @param reg The RegistryManager
            int _btnFctMap2(eng::RegistryManager &reg);

            /// @brief fct for button map 3
            /// @param reg The RegistryManager
            int _btnFctMap3(eng::RegistryManager &reg);
        private:
            eng::RegistryManager &_manager;
            std::function<int(eng::RegistryManager&, bool, int, int)> &_co;
    };
}

#endif /* !MAPVOTER_HPP_ */
