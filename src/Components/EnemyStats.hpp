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
            EnemyStats(int pHealth = 10): health(pHealth)
            {}
            ~EnemyStats() {}

            int health;
        protected:
        private:
    };
} // namespace rtp



#endif /* !ENEMYSTATS_HPP_ */
