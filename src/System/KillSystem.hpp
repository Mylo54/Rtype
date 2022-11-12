/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** KillSystem
*/

#ifndef KILLSYSTEM_HPP_
#define KILLSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Bullet.hpp"
#include "../GameComponent/EnemyStats.hpp"
#include "../System/TextSystem.hpp"
#include <sstream>

namespace rtp
{
    class KillSystem {
        public:
            KillSystem();
            ~KillSystem();
        void killOutOfBounds(eng::Registry &reg);
        void killBullets(eng::Registry &reg);
        void killDeadEnemies(eng::Registry &r, int &score, rtp::TextSystem &text);
        protected:
        private:
    };

} // namespace rtp

#endif /* !KILLSYSTEM_HPP_ */
