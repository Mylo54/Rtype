/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Velocity
*/

#ifndef VELOCITY_HPP_
#define VELOCITY_HPP_

namespace rtp
{
    /// @brief A class holding the velocity of an entity
    class Velocity {
        public:
            /// @brief Velocity object constructor
            /// @param _x horizontal velocity
            /// @param _y vertical velocity
            Velocity(float _x = 0, float _y = 0): x(_x), y(_y) {} 
            ~Velocity() {}

            float x;
            float y;
        protected:
        private:
    };
} // namespace rtp



#endif /* !VELOCITY_HPP_ */
