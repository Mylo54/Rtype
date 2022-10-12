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
            PlayerStats(int playerID,
            int pHealth = 10,
            int pDamage = 1,
            int pLives = 3): playerId(playerID), health(pHealth), damage(pDamage), lives(pLives)
            {}
            ~PlayerStats() {}

            int playerId;
            int health;
            int damage;
            int lives;
        protected:
        private:
    };
} // namespace rtp

#endif /* !PLAYERSTATS_HPP_ */
