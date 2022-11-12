/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** TextSystem
*/

#ifndef TEXTSYSTEM_HPP_
#define TEXTSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Bullet.hpp"
#include "../GameComponent/EnemyStats.hpp"
#include <sstream>

namespace rtp
{
    class TextSystem {
        public:
            enum ChatBoxStyle {
                    CHAT,
                    EVENT
            };
            TextSystem();
            ~TextSystem();
            void setText(eng::Registry &r, std::string message, std::string name,  rtp::TextSystem::ChatBoxStyle style);
        protected:
        private:
    };
} // namespace rtp

#endif /* !TEXTSYSTEM_HPP_ */