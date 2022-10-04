/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Drawable
*/

#ifndef DRAWABLE_HPP_
#define DRAWABLE_HPP_

#include "iostream"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

namespace rtp
{
    class Drawable {
        public:
            /// @brief A component holding your sprite
            /// @param textureFilePath path to your Sprite
            /// @param pwindow a reference to the window
            /// @param pSheetDirection the direction of your spritesheet
            /// [0:none]
            /// [1:left to right]
            /// [2:right to left]
            /// [3:up to down]
            /// [4:down to up]
            /// @param rect the dimensions of one sprite in your spritesheet
            /// @param pFrameTime how much time from one frame to another
            Drawable(std::string textureFilePath,
            sf::RenderWindow &pwindow,
            sf::Clock &pclock,
            int pSheetDirection = 0,
            sf::IntRect rect = {0, 0, 0, 0},
            float pFrameTime = 1) : window(pwindow), clock(pclock) {
                sheetDirection = pSheetDirection;
                texture->loadFromFile(textureFilePath);
                sprite.setTexture(*texture);
                sizeX = texture->getSize().x;
                sizeY = texture->getSize().y;
                frameTime = pFrameTime;
                if (sheetDirection != 0)
                    sprite.setTextureRect(rect);
            }
            ~Drawable() {}

            int sheetDirection;
            float frameTime;
            float nextFrame = 0;
            sf::RenderWindow &window;
            sf::Clock &clock;
            sf::Texture *texture = new sf::Texture;
            sf::Sprite sprite;
            int sizeX;
            int sizeY;
        protected:
        private:
    };
} // namespace rtp



#endif /* !DRAWABLE_HPP_ */
