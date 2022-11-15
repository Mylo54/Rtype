/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** PlayerSystem
*/

#ifndef PLAYERSYSTEM_HPP_
#define PLAYERSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Controllable.hpp"
#include "../GameComponent/Shooter.hpp"
#include "../GameComponent/Canon.hpp"
#include "../GameComponent/Bullet.hpp"
#include "../GameComponent/PlayerStats.hpp"
#include <sstream>

namespace rtp
{
    class PlayerSystem {
        public:
            PlayerSystem();
            ~PlayerSystem();

            /// @brief A system who handles inputs and stores actions
            /// @param reg The registry on which to apply the system
            void control(eng::Registry &reg, eng::SuperInput &input);
            /// @brief 
            /// @param reg 
            /// @param input 
            /// @param delta as seconds
            void controlMovement(eng::Registry &reg, float delta);
            void controlFireSystem(eng::Registry &reg, float delta);
            void shootSystem(eng::Registry &reg);
            void limitPlayer(eng::Registry &reg);
            /// @brief Adds a controllable player to a registry
            /// @param playerId The player id (1, 2, 3 or 4)
            /// @param syncId The sync component id
            /// @return The entity containing the player
            eng::Entity addPlayer(eng::Registry &reg, eng::TextureManager &texture, int playerId, int syncId);
        protected:
        private:
    };
} // namespace rtp


#endif /* !PLAYERSYSTEM_HPP_ */
