/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

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

namespace rtp {
    class Game {
        public:
            Game(eng::RegistryManager &manager);
            ~Game();
            
        protected:
            /// @brief Setup the registry with every sparse array needed
            /// @param r The Registry to setup
            void _setupRegistry(eng::Registry &reg);

            /// @brief Adds a music to the registry
            /// @param reg the registry on which to add the music
            /// @param filepath the filepath on where to find the music
            void _addMusic(eng::Registry &reg, std::string filepath);

            /// @brief Adds a controllable player to a registry
            /// @param reg The Registry on which to adds the player 
            /// @param playerId The player id (1, 2, 3 or 4)
            /// @param syncId The sync component id
            /// @return The entity containing the player
            eng::Entity _addPlayer(eng::Registry &reg, int playerId, int syncId);

            /// @brief Adds an enemy to a registry
            /// @param reg The Registry on which to adds the enemy 
            /// @return The entity containing the enemy
            eng::Entity _addEnemy(eng::Registry &reg);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds(eng::Registry &reg);

            /// @brief Add a text on the screen to display the score
            /// @param reg The registry on which to add the text
            void _addScore(eng::Registry &reg);
        private:
            eng::RegistryManager &_manager;
    };
}

#endif /* !GAME_HPP_ */
