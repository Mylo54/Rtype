/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** BackgroundSystem
*/

#ifndef BACKGROUNDSYSTEM_HPP_
#define BACKGROUNDSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Background.hpp"

namespace rtp
{
    class BackgroundSystem {
        public:
            BackgroundSystem();
            ~BackgroundSystem();
            void loop(eng::Registry &r);
        protected:
        private:
    }; 
} // namespace rtp


#endif /* !BACKGROUNDSYSTEM_HPP_ */
