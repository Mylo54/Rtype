/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** TextSystem
*/

#include "TextSystem.hpp"

rtp::TextSystem::TextSystem()
{
}

rtp::TextSystem::~TextSystem()
{
}

void rtp::TextSystem::setText(eng::Registry &r, std::string message, std::string name,  rtp::TextSystem::ChatBoxStyle style)
{
    auto &writables = r.getComponents<eng::Writable>();

    for (int i = 0; i < writables.size(); i++) {
        auto &wrt = writables[i];
        if (wrt.has_value() && wrt.value()._name == name) {
            wrt.value()._txt.setString(message);
            if (style == rtp::TextSystem::CHAT) {
                wrt.value()._txt.setStyle(sf::Text::Regular);
                wrt.value()._txt.setFillColor(sf::Color::White);
            }
            if (style == rtp::TextSystem::EVENT) {
                wrt.value()._txt.setStyle(sf::Text::Italic);
                wrt.value()._txt.setFillColor(sf::Color::Blue);
            }
        }
    }
}