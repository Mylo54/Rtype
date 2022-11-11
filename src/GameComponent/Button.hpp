/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Button
*/

#ifndef BUTTON_HPP_
#define BUTTON_HPP_

#include <iostream>
#include <functional>
#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp
{
    class Button {
        public:
            /// @brief background object contructor
            /// @param btnFunction_ This function will be executed when releasing the button
            /// @param top_ Y coordinate of the top-left corner
            /// @param left_ X coordinate of the top-left corner
            /// @param width_ Width (in pixels) of your button
            /// @param height_ Height (in pixels) of your button

            Button(std::function<int ()> btnFunction_, int top_, int left_,
            int width_, int height_): btnFunction(btnFunction_), top(top_),
            left(left_), width(width_), height(height_)
            {}
            ~Button() {}

            std::function<int()> btnFunction;
            int top;
            int left;
            int width;
            int height;
        protected:
        private:
    };
} // namespace rtp



#endif /* !BUTTON_HPP_ */
