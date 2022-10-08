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
    class Bullet {
    public:
        Bullet(int pDamage = 1): damage(pDamage)
        {}
        ~Bullet() {}

        int damage;
    protected:
    private:
};
} // namespace rtp



#endif /* !BULLET_HPP_ */
