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
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp {
    class Game : public AScene {
        public:

            /// @brief Gamr object constructor
            Game(rtp::scene_package_t pack);
            ~Game();

            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;

            /// @brief Adds a controllable player to a registry
            /// @param playerId The player id (1, 2, 3 or 4)
            /// @param syncId The sync component id
            /// @return The entity containing the player
            eng::Entity addPlayer(int playerId, int syncId);
            
        protected:

            /// @brief Adds a music to the registry
            void _addMusic();

            /// @brief Adds an enemy to a registry
            /// @param reg The Registry on which to adds the enemy 
            /// @return The entity containing the enemy
            eng::Entity _addEnemy();

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds();

            /// @brief Add a text on the screen to display the score
            /// @param reg The registry on which to add the text
            void _addScore();
        private:
    };
}

#endif /* !GAME_HPP_ */
