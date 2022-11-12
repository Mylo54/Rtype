/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** EnemySystem
*/

#ifndef ENEMYSYSTEM_HPP_
#define ENEMYSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../GameComponent/Background.hpp"
#include "../GameComponent/Bullet.hpp"
#include "../GameComponent/EnemyStats.hpp"

namespace rtp
{
    class EnemySystem {
        public:
            EnemySystem();
            ~EnemySystem();
            eng::Entity _addEnemy(eng::Registry &reg, eng::TextureManager &texture);
            void playerBullets(eng::Registry &r);
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);
        protected:
        private:
    }; 
} // namespace rtp


#endif /* !ENEMYSYSTEM_HPP_ */
