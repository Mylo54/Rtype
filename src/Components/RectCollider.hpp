/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** RectCollider
*/

#ifndef RECTCOLLIDER_HPP_
#define RECTCOLLIDER_HPP_

namespace rtp
{
    /// @brief A class holding the hitbox of entities
    /// Tips : Don't use the colliders from the sfml because this component will likely go into the server after the split
    class RectCollider {
    public:
        /// @brief RectCollider object constructor
        /// @param pWidth width of the hitbox
        /// @param pHeight height of the hitbox
        RectCollider(int pWidth, int pHeight): width(pWidth), height(pHeight)
        {}
        ~RectCollider() {}

        int width;
        int height;
        bool hasCollided = false;
        int entityIdx = 0;
    protected:
    private:
};
} // namespace rtp



#endif /* !RECTCOLLIDER_HPP_ */
