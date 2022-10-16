/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Writable
*/

#ifndef WRITABLE_HPP_
#define WRITABLE_HPP_

#include "iostream"
#include "SFML/Window.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/System/String.hpp"

namespace rtp
{
    class Writable {
        public:
            Writable(std::string name,
            sf::String content = "Text",
            const std::string fontPath = "assets/MetroidPrimeHunters.ttf",
            unsigned int charSize = 30,
            sf::Color color = sf::Color::White,
            sf::Text::Style style = sf::Text::Regular) {
                _font->loadFromFile(fontPath);
                _content = &content;
                _color = &color;
                _txt.setString(*_content);
                _txt.setCharacterSize(charSize);
                _txt.setFont(*_font);
                _txt.setFillColor(*_color);
                _txt.setStyle(style);
                _name = name;
            }
            ~Writable() {}
            sf::String *_content = new sf::String;
            sf::Font *_font = new sf::Font;
            sf::Color *_color = new sf::Color;
            sf::Text _txt;
            std::string _name;
        protected:
        private:
    };
} // namespace rtp

#endif /* !WRITABLE_HPP_ */