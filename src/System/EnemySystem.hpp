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

namespace rtp
{
    class EnemySystem {
        public:
            EnemySystem();
            ~EnemySystem();
            eng::Entity _addEnemy(eng::Registry &reg, eng::TextureManager &texture);
        protected:
        private:
    }; 
} // namespace rtp


#endif /* !ENEMYSYSTEM_HPP_ */
