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

namespace rtp
{
    class KillSystem {
        public:
            KillSystem();
            ~KillSystem();
        void killOutOfBounds(eng::Registry &reg);
        void killBullets(eng::Registry &reg);
        void killDeadEnemies(eng::Registry &r);
        protected:
        private:
    };

    #endif /* !KILLSYSTEM_HPP_ */
} // namespace rtp

