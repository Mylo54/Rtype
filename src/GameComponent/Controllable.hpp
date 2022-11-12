/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include "SFML/Window.hpp"
#include <iostream>
#include <functional>
#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp
{
    /// @brief A class handling every controllable components
    class Controllable {
        public:
            /// @brief Controllable object constructor
            Controllable() {}
            ~Controllable() {}

            int xAxis = 0;
            int yAxis = 0;
            bool shoot = false;
            bool canonShoot = false;
            bool hasShot = false;
            bool event = false;
            char count = 'a';
        protected:
        private:
    };
} // namespace rtp



#endif /* !CONTROLLABLE_HPP_ */
