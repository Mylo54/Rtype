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

namespace rtp
{
    class PlayerSystem {
        public:
            PlayerSystem();
            ~PlayerSystem();

            /// @brief A system who handles inputs and stores actions
            /// @param reg The registry on which to apply the system
            void control(eng::Registry &reg, eng::SuperInput &input);
        protected:
        private:
    };
} // namespace rtp


#endif /* !PLAYERSYSTEM_HPP_ */
