/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** ButtonSystem
*/

#include "ButtonSystem.hpp"

rtp::ButtonSystem::ButtonSystem()
{
}

rtp::ButtonSystem::~ButtonSystem()
{
}

void rtp::ButtonSystem::buttonStateSystem(eng::Registry &reg, eng::SuperInput &input)
{
    auto &buttons = reg.getComponents<rtp::Button>();
    auto &positions = reg.getComponents<eng::Position>();
    auto &sprite = reg.getComponents<eng::Drawable>();
    auto mousePos = input.getMousePosition();

    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].has_value()) {
            auto &btn = buttons[i].value();
            auto &spr = sprite[i].value();
            auto &pos = positions[i].value();
            sf::IntRect rect = spr.sprite.getTextureRect();

            if (mousePos[0] > pos.x && mousePos[0] < pos.x + btn.width
            && mousePos[1] > pos.y && mousePos[1] < pos.y + btn.height) {
                rect.left = (spr.sheetDirection == 1) ? rect.width : 0;
                rect.top = (spr.sheetDirection == 3) ? rect.height : 0;
                    if (input.isActionPressed("ui_click")) {
                        rect.left += (spr.sheetDirection == 1) ? rect.width : 0;
                        rect.top += (spr.sheetDirection == 3) ? rect.height : 0;
                    }
            } else {
                rect.left = (spr.sheetDirection == 1) ? 0 : rect.width;
                rect.top = (spr.sheetDirection == 3) ? 0 : rect.height;
            }
            spr.sprite.setTextureRect(rect);
        }
    }
}

void rtp::ButtonSystem::buttonClick(eng::Registry &reg, eng::SuperInput &input)
{
    auto &buttons = reg.getComponents<Button>();
    auto &positions = reg.getComponents<eng::Position>();
    auto mousePos = input.getMousePosition();

    if (input.isActionJustReleased("ui_click")) {
        for (int i = 0; i < buttons.size() && i < positions.size(); i++) {
            if (buttons[i].has_value() && positions[i].has_value()) {
                auto &btn = buttons[i].value();
                auto &pos = positions[i].value();

                if (mousePos[0] > pos.x && mousePos[0] < pos.x + btn.width
                && mousePos[1] > pos.y && mousePos[1] < pos.y + btn.height) {
                    // btn.btnFunction(manager);
                }
            }
        }
        return;
    }
}