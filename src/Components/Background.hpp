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
    /// @brief A class holding a background visual element
    class Background {
        public:
            /// @brief Background object constructor
            /// @param textureFilePath path to the texture file to load
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
