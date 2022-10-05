/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Systems
*/

#include "Systems.hpp"

rtp::Systems::Systems(sf::RenderWindow &w, sf::Clock &c) : _w(w), _c(c)
{
}

rtp::Systems::~Systems()
{
}

void rtp::Systems::logSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            std::cout << i << ": pos = {" << pos.value().x << ", " << pos.value().y;
            std::cout << ", " << pos.value().z << "}, vel = {" << vel.value().x;
            std::cout << ", " << vel.value().y << "}" << std::endl;
        }
    }
}

void rtp::Systems::controlSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &controllables = r.getComponents<Controllable>();
    float speed = 1;

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                vel.value().x = vel.value().x - speed;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                vel.value().x = vel.value().x + speed;
            else {
                if (vel.value().x > 0)
                    vel.value().x -= speed;
                else if (vel.value().x < 0)
                    vel.value().x += speed;
            }
            
            // Up & Down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                vel.value().y = vel.value().y - speed;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                vel.value().y = vel.value().y + speed;
            else {
                if (vel.value().y > 0)
                    vel.value().y -= speed;
                else if (vel.value().y < 0)
                    vel.value().y += speed;
            }
        }
    }
}

void rtp::Systems::clearSystem(eng::Registry &r)
{
    _w.clear();
}

void rtp::Systems::displaySystem(eng::Registry &r)
{
    _w.display();
    _c.restart();
}

// Needs to change some things here...
void rtp::Systems::drawSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &sprites = r.getComponents<Drawable>();

    // Draw & update sheets
    for (int i = 0; i < positions.size() && i < sprites.size(); i++) {
        auto &pos = positions[i];
        auto &spr = sprites[i];

        if (pos.has_value() && spr.has_value()) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection != 0) {
                spr.value().nextFrame -= _c.getElapsedTime().asSeconds();
            }
            // Animate to the right
            if (spr.value().sheetDirection == 1 && spr.value().nextFrame <= 0) {
                rect.left += rect.width;
                if (rect.left >= spr.value().sizeX)
                    rect.left = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            spr.value().sprite.setTextureRect(rect);
            spr.value().sprite.setPosition({pos.value().x, pos.value().y});
            _w.draw(spr.value().sprite);
        }
    }
}

void rtp::Systems::controlFireSystem(eng::Registry &r)
{
    auto &shooters = r.getComponents<Shooter>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < shooters.size(); i++) {
        auto &sht = shooters[i];
        auto &ctrl = controllables[i];

        if (sht.has_value() && ctrl.has_value()) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  {
                sht.value().shoot = true;
            }
        }
    }
}

void rtp::Systems::backgroundSystem(eng::Registry &r)
{
    auto &bgs = r.getComponents<Background>();
    auto &poss = r.getComponents<Position>();

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

void rtp::Systems::shootSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &shooters = r.getComponents<Shooter>();

    for (int i = 0; i < positions.size() && i < shooters.size(); i++) {
        auto &pos = positions[i];
        auto &sht = shooters[i];
        
        if (pos.has_value() && sht.has_value()) {
            if (sht.value().shoot) {
                float x = pos.value().x + sht.value().shootPoint[0];
                float y = pos.value().y + sht.value().shootPoint[1];
                float z = pos.value().z;
                sht.value().shoot = false;
                eng::Entity bullet = r.spawnEntity();
                r.addComponent(bullet, rtp::Velocity(15, 0));
                r.addComponent(bullet, rtp::Position(x, y, z));
                r.addComponent(bullet, rtp::Drawable(sht.value().bulletSpritePath, _w, _c));
                r.addComponent(bullet, rtp::AudioSource("../assets/fire.wav", true));
            }
        }
    }
}

void rtp::Systems::playSoundSystem(eng::Registry &r)
{
    auto &sounds = r.getComponents<AudioSource>();

    for (int i = 0; i < sounds.size(); i++) {
        auto &snd = sounds[i];

        if (snd.has_value()) {
            if (snd.value().toPlay) {
                snd.value().toPlay = false;
                snd.value().sound.play();
            }
        }
    }
}

void rtp::Systems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += vel.value().x;
            pos.value().y += vel.value().y;
        }
    }
}

void rtp::Systems::sendData(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size(); i++) {
        auto ctrl = controllables[i];

        if (ctrl.has_value()) {
            // Inputs will be inside the ctrl.value() object
            std::cout << "I send the inputs" << std::endl;
        }
    }

}

void rtp::Systems::receiveData(eng::Registry &r)
{
    // Read the buffer of values received from the server
    // For every entity having the "Synced" component (not existing yet),
    // Emplace new values (Position, health, Velocities, etc ...)
}