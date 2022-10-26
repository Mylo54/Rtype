/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsSystems
*/

#include "GraphicsSystems.hpp"

rtp::GraphicsSystems::GraphicsSystems(std::vector<int> dimWdw,
std::string nameWdw):
_w(sf::RenderWindow(sf::VideoMode(dimWdw[0], dimWdw[1], dimWdw[2]), nameWdw)),
_c(sf::Clock())
{
}

rtp::GraphicsSystems::~GraphicsSystems()
{
}

void rtp::GraphicsSystems::drawSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
    auto &sprites = r.getComponents<eng::Drawable>();

    // Draw & update sheets
    for (int i = 0; i < positions.size() && i < sprites.size(); i++) {
        auto &pos = positions[i];
        auto &spr = sprites[i];

        if (pos.has_value() && spr.has_value()) {
            spr.value().sprite.setPosition({pos.value().x, pos.value().y});
            _w.draw(spr.value().sprite);
        }
    }
}

void rtp::GraphicsSystems::backgroundSystem(eng::Registry &r)
{
    auto &bgs = r.getComponents<Background>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < bgs.size() && i < poss.size(); i++) {
        auto &pos = poss[i];
        auto &bg = bgs[i];

        if (pos.has_value() && bg.has_value()) {
            if (pos.value().x <= -1920)
                pos.value().x = 1920;
            bg.value().sprite.setPosition({pos.value().x, pos.value().y});
            _w.draw(bg.value().sprite);
        }
    }
}

void rtp::GraphicsSystems::writeSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
    auto &writables = r.getComponents<eng::Writable>();

    for (int i = 0; i < positions.size() && i < writables.size(); i++) {
        auto &pos = positions[i];
        auto &wrt = writables[i];

        if (pos.has_value() && wrt.has_value()) {
            wrt.value()._txt.setPosition({pos.value().x, pos.value().y});
            _w.draw(wrt.value()._txt);
        }
    }
}

bool rtp::GraphicsSystems::windowOpen()
{
    return this->_w.isOpen();
}

void rtp::GraphicsSystems::eventCatchWindow()
{
    while (this->_w.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_w.close();
        if (this->_event.type == sf::Event::GainedFocus)
            this->_isWindowFocused = true;
        if (this->_event.type == sf::Event::LostFocus)
            this->_isWindowFocused = false;
    }
}

void rtp::GraphicsSystems::buttonStateSystem(eng::Registry &r)
{
    auto &buttons = r.getComponents<Button>();
    auto &positions = r.getComponents<eng::Position>();
    auto &sprite = r.getComponents<eng::Drawable>();
    auto mousePos = sf::Mouse::getPosition(_w);

    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].has_value()) {
            auto &btn = buttons[i].value();
            auto &spr = sprite[i].value();
            auto &pos = positions[i].value();
            sf::IntRect rect = spr.sprite.getTextureRect();

            if (mousePos.x > pos.x && mousePos.x < pos.x + btn.width
            && mousePos.y > pos.y && mousePos.y < pos.y + btn.height) {
                rect.left = (spr.sheetDirection == 1) ? rect.width : 0;
                rect.top = (spr.sheetDirection == 3) ? rect.height : 0;
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
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

void rtp::GraphicsSystems::controlSystem(eng::Registry &r)
{
    if (_isWindowFocused == false) {
        return;
    }
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            // up and down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                ctrl.value().yAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                ctrl.value().yAxis = 1;
            else
                ctrl.value().yAxis = 0;
            
            // left and right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                ctrl.value().xAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                ctrl.value().xAxis = 1;
            else
                ctrl.value().xAxis = 0;
            
            // shoot
            ctrl.value().shoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
        }
    }
}

void rtp::GraphicsSystems::clearSystem()
{
    this->_w.clear();
}

void rtp::GraphicsSystems::setMaxFrameRate(unsigned int mfr)
{
    this->_w.setFramerateLimit(mfr);
}

sf::RenderWindow &rtp::GraphicsSystems::getWindow()
{
    return this->_w;
}

sf::Clock &rtp::GraphicsSystems::getClock()
{
    return this->_c;
}

sf::Time &rtp::GraphicsSystems::getDelta()
{
    return this->_delta;
}

/* 
        if (spr.has_value()) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection != 0)
                spr.value().nextFrame -= _delta.asSeconds();

            if (spr.value().nextFrame <= 0) {
                rect.left += (spr.value().sheetDirection == 1) ? rect.width : 0;
                rect.left -= (spr.value().sheetDirection == 2) ? rect.width : 0;
                rect.top += (spr.value().sheetDirection == 3) ? rect.height : 0;
                rect.top -= (spr.value().sheetDirection == 4) ? rect.height : 0;

                rect.left = (rect.left >= spr.value().sizeX) ? 0 : rect.left;
                rect.top = (rect.top >= spr.value().sizeY) ? 0 : rect.top;
                rect.left = (rect.left < 0) ? spr.value().sizeX : rect.left;
                rect.top = (rect.top < 0) ? spr.value().sizeY : rect.top;

                spr.value().nextFrame = spr.value().frameTime;
                spr.value().sprite.setTextureRect(rect);
            }
        }
*/
void rtp::GraphicsSystems::animateSystem(eng::Registry &r)
{
    auto &sprites = r.getComponents<eng::Drawable>();

    for (int i = 0; i < sprites.size(); i++) {
        auto &spr = sprites[i];
        
        if (spr.has_value() && spr.value().frameTime != -1) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection != 0) {
                spr.value().nextFrame -= _delta.asSeconds();
            }
            // Animate to the right
            if (spr.value().sheetDirection == 1 && spr.value().nextFrame <= 0) {
                rect.left += rect.width;
                if (rect.left >= spr.value().sizeX)
                    rect.left = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate to the left
            if (spr.value().sheetDirection == 2 && spr.value().nextFrame <= 0) {
                rect.left -= rect.width;
                if (rect.left < 0)
                    rect.left = spr.value().sizeX;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate downward
            if (spr.value().sheetDirection == 3 && spr.value().nextFrame <= 0) {
                rect.top += rect.height;
                if (rect.top >= spr.value().sizeY)
                    rect.top = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate upward
            if (spr.value().sheetDirection == 4 && spr.value().nextFrame <= 0) {
                rect.top -= rect.height;
                if (rect.top < 0)
                    rect.top = spr.value().sizeY;
                spr.value().nextFrame = spr.value().frameTime;
            }
            spr.value().sprite.setTextureRect(rect);
        }
    }
}

void rtp::GraphicsSystems::displaySystem()
{
    _w.display();
    _delta = _c.restart();
}