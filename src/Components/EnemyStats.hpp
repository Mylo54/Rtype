/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** EnemyStats
*/

#ifndef ENEMYSTATS_HPP_
#define ENEMYSTATS_HPP_

namespace rtp
{
    class EnemyStats {
        public:
            /// @brief EnemyStats object constructor
            /// @param pHealth HP of the enemy (10 by default)
            /// @param pEnemyType type of the enemy (0 by default)
            EnemyStats(int pHealth = 10, int pEnemyType = 0): health(pHealth), enemyType(pEnemyType)
            {}
            ~EnemyStats() {}

            int health;
            int enemyType;
        protected:
        private:
    };
} // namespace rtp



#endif /* !ENEMYSTATS_HPP_ */
