/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Bonus
*/

#ifndef BONUS_HPP_
#define BONUS_HPP_

namespace rtp
{
    /// @brief A class holding Bonus statistics
    class Bonus {
        public:
            /// @brief Bonus object constructor
            Bonus(int ptype = 0): type(ptype)
            {}
            ~Bonus() {}

            int type;
        protected:
        private:
    };
} // namespace rtp

#endif /* !BONUS_HPP_ */
