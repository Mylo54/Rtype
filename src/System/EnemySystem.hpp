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
#include "../GameComponent/PlayerStats.hpp"

namespace rtp
{
    class EnemySystem {
        public:
            EnemySystem();
            ~EnemySystem();
            eng::Entity _addEnemy(eng::Registry &reg, eng::TextureManager &texture);
            void playerBullets(eng::Registry &r);
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);
            void enemyCollision(eng::Registry &r, eng::PhysicSystems &physic);
            void spawnEnemies(eng::Registry &r, float &enemyTimer, int level, float delta, eng::TextureManager &texture);
        protected:
        private:
    }; 
} // namespace rtp


#endif /* !ENEMYSYSTEM_HPP_ */
