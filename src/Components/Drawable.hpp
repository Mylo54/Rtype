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
            Drawable(std::string textureFilePath, sf::RenderWindow &pwindow, bool pSheetDirection = 0, sf::IntRect rect = {0, 0, 0, 0}) : window(pwindow) {
                sheetDirection = pSheetDirection;
                texture->loadFromFile(textureFilePath);
                sprite.setTexture(*texture);
                sizeX = texture->getSize().x;
                sizeY = texture->getSize().y;
                if (sheetDirection != 0)
                    sprite.setTextureRect(rect);
            }
            ~Drawable() {}

            int sheetDirection;
            sf::RenderWindow &window;
            sf::Texture *texture = new sf::Texture;
            sf::Sprite sprite;
            int sizeX;
            int sizeY;
        protected:
        private:
    };
} // namespace rtp



#endif /* !DRAWABLE_HPP_ */
