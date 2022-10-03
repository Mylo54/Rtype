/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Controllable
*/

#ifndef CONTROLLABLE_HPP_
#define CONTROLLABLE_HPP_

#include "SFML/Window.hpp"

namespace rtp
{
    class Controllable {
        public:
            Controllable(sf::RenderWindow &pwindow): window(pwindow) {}
            ~Controllable() {}

            sf::RenderWindow &window;
        protected:
        private:
    };
} // namespace rtp



#endif /* !CONTROLLABLE_HPP_ */
