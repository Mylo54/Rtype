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
    /// @brief A class holding Player statistics
    class PlayerStats {
        public:
            /// @brief PlayerStats object constructor
            /// @param playerID 
            /// @param pDamage 
            /// @param pLives 
            PlayerStats(int playerID,
            int pDamage = 1,
            int pLives = 3): playerId(playerID), damage(pDamage), lives(pLives)
            {}
            ~PlayerStats() {}

            int playerId;
            int damage;
            int lives;
            int score = 0;
        protected:
        private:
    };
} // namespace rtp

#endif /* !PLAYERSTATS_HPP_ */
