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
#include "../GameComponent/Controllable.hpp"
#include "../GameComponent/PlayerStats.hpp"
#include "../GameComponent/Shooter.hpp"
#include "../GameComponent/Canon.hpp"
#include "../GameComponent/Bullet.hpp"

namespace rtp {
    class Game : public AScene {
        public:

            /// @brief Gamr object constructor
            Game(rtp::scene_package_t pack, std::vector<int> &startGamePayload);
            ~Game();

            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
            
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
            float _enemyTimer;
            std::vector<int> &_startGamePayload;
    };
}

#endif /* !GAME_HPP_ */
