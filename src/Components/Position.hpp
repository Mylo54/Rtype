/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Position
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

namespace rtp
{
    /// @brief A class holding the positions of entities
    class Position {
        public:
            /// @brief Position object constructor
            /// @param _x horizontal position
            /// @param _y vertical position
            /// @param _z depth position
            Position(float _x, float _y, float _z): x(_x), y(_y), z(_z) {} 
            ~Position() {}
        
            float x;
            float y;
            float z;
        protected:
        private:
    };
} // namespace rtp



#endif /* !POSITION_HPP_ */
