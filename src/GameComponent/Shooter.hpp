/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Shooter
*/

#ifndef SHOOTER_HPP_
#define SHOOTER_HPP_

#include <iostream>
#include <vector>

namespace rtp
{
    /// @brief A class handling shooting action
    class Shooter {
        public:
            /// @brief Shooter object constructor
            /// @param pBulletSpritePath path to the Sprite of the projectile
            /// @param pSpeed speed of the projectile
            /// @param pFireRate fire rate of the shooting entity
            /// @param pShootPoint the shoot point of the shooting entity
            Shooter(std::string pBulletSpritePath,
            float pSpeed,
            float pFireRate,
            std::vector<float> pShootPoint = {0, 0}) : bulletSpritePath(pBulletSpritePath), speed(pSpeed), shootPoint(pShootPoint)
            {
                // Hz to kHz
                fireRate = (1 / pFireRate);
            }
            ~Shooter() {}

            std::string bulletSpritePath;
            float speed;
            float fireRate;
            std::vector<float> shootPoint;
            bool shoot = false;
            float nextFire = 0;
        protected:
        private:
    };
} // namespace rtp

#endif /* !SHOOTER_HPP_ */
