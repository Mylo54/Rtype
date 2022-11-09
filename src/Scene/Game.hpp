// /*
// ** EPITECH PROJECT, 2022
// ** rtype
// ** File description:
// ** Game
// */

// #ifndef GAME_HPP_
// #define GAME_HPP_

// #include <iostream>
// #include <fstream>
// #include "AScene.hpp"

// namespace rtp {
//     class Game : public AScene {
//         public:

//             /// @brief Gamr object constructor
//             /// @param manager reference to registry manager
//             Game(rtp::scene_package_t &pack, eng::RegistryManager &manager);
//             ~Game();

//             /// @brief Adds a controllable player to a registry
//             /// @param reg The Registry on which to adds the player 
//             /// @param playerId The player id (1, 2, 3 or 4)
//             /// @param syncId The sync component id
//             /// @return The entity containing the player
//             eng::Entity addPlayer(eng::Registry &reg, int playerId, int syncId);
            
//         protected:

//             /// @brief Adds a music to the registry
//             /// @param reg the registry on which to add the music
//             /// @param filepath the filepath on where to find the music
//             void _addMusic(eng::Registry &reg, std::string filepath);

//             /// @brief Adds an enemy to a registry
//             /// @param reg The Registry on which to adds the enemy 
//             /// @return The entity containing the enemy
//             eng::Entity _addEnemy(eng::Registry &reg);

//             /// @brief Add layers of backgrounds to a registry
//             /// @param reg The Registry on which to add the backgrounds
//             void _addBackgrounds(eng::Registry &reg);

//             /// @brief Add a text on the screen to display the score
//             /// @param reg The registry on which to add the text
//             void _addScore(eng::Registry &reg);
//         private:
//             eng::RegistryManager &_manager;
//     };
// }

// #endif /* !GAME_HPP_ */
