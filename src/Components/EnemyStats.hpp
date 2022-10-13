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
