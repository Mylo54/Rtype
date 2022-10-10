/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** PlayerStats
*/

#ifndef PLAYERSTATS_HPP_
#define PLAYERSTATS_HPP_

namespace rtp
{
    class PlayerStats {
        public:
            PlayerStats(int pHealth = 10,
            int pDamage = 1,
            int pLives = 3): health(pHealth), damage(pDamage), lives(pLives)
            {}
            ~PlayerStats() {}

            int health;
            int damage;
            int lives;
        protected:
        private:
    };
} // namespace rtp

#endif /* !PLAYERSTATS_HPP_ */
