/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "../Engine/Registry.hpp"
#include "../Components/Drawable.hpp"
#include "../Components/Controllable.hpp"
#include "../Components/Position.hpp"
#include "../Components/Velocity.hpp"

namespace rtp
{
    class Systems {
        public:
            Systems();
            ~Systems();

            void positionSystem(eng::Registry &r);
            void drawSystem(eng::Registry &r);
            void controlSystem(eng::Registry &r);
            void logSystem(eng::Registry &r);
        protected:
        private:
    };
} // namespace rtp



#endif /* !SYSTEMS_HPP_ */
