/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Bullet
*/

#ifndef BULLET_HPP_
#define BULLET_HPP_

namespace rtp
{
    /// @brief A class holding in game projectiles
    class Bullet {
        public:
            /// @brief Bullet object constructor
            /// @param pDamage damage dealt by the projectile (1 by default)
            Bullet(int pDamage = 1): damage(pDamage)
            {}
            ~Bullet() {}
    
            int damage;
        protected:
        private:
    };
} // namespace rtp

#endif /* !BULLET_HPP_ */
