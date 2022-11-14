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
    /// @brief A class holding Enemy statistics
    class EnemyStats {
        public:
            /// @brief EnemyStats object constructor
            /// @param pHealth HP of the enemy (10 by default)
            /// @param pEnemyType type of the enemy (0 by default)
            EnemyStats(int pHealth = 10, int pEnemyType = 0, float plifeTime = 10): health(pHealth), enemyType(pEnemyType), lifeTime(plifeTime)
            {}
            ~EnemyStats() {}

            int health;
            int enemyType;
            float lifeTime;
        protected:
        private:
    };
} // namespace rtp



#endif /* !ENEMYSTATS_HPP_ */
