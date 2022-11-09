/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** ButtonSystem
*/

#ifndef BUTTONSYSTEM_HPP_
#define BUTTONSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Button.hpp"

namespace rtp
{
    class ButtonSystem {
        public:
            ButtonSystem();
            ~ButtonSystem();

            /// @brief A system who set the state of a button according
            /// @param r The Registry on which to apply the system
            /// @param input Inputs of the player
            void buttonStateSystem(eng::Registry &r, eng::SuperInput &input);

            /// @brief A system who handle button clicking
            /// @param r The registry on which to apply the system
            /// @param input Inputs of the player
            void buttonClick(eng::Registry &r, eng::SuperInput &input);
        protected:
        private:
    };
} // namespace rtp


#endif /* !BUTTONSYSTEM_HPP_ */
