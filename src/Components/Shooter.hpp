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
    class Shooter {
        public:
            Shooter(std::string pBulletSpritePath,
            float pSpeed,
            std::vector<float> pShootPoint) : bulletSpritePath(pBulletSpritePath), speed(pSpeed), shootPoint(pShootPoint)
            {}
            ~Shooter() {}

            std::string bulletSpritePath;
            float speed;
            std::vector<float> shootPoint;
            bool shoot = false;
        protected:
        private:
    };
} // namespace rtp



#endif /* !SHOOTER_HPP_ */
