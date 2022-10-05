/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Background
*/

#ifndef BACKGROUND_HPP_
#define BACKGROUND_HPP_

#include <iostream>
#include <SFML/Graphics.hpp>

namespace rtp
{
    class Background {
        public:
            Background(std::string textureFilePath)
            {
                texture->loadFromFile(textureFilePath);
                sprite.setTexture(*texture);
            }
            ~Background() {}

            sf::Texture *texture = new sf::Texture;
            sf::Sprite sprite;
        protected:
        private:
    };
} // namespace rtp



#endif /* !BACKGROUND_HPP_ */
