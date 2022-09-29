/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include "../Client/Client.hpp"

int main(int argc, char **argv)
{
    const float FPS = 60.0f; //The desired FPS. (The number of updates each second).
    bool redraw = true;      //Do I redraw everything on the screen?

    sf::RenderWindow window(sf::VideoMode(300, 300, 32), "Rutabaga");
    window.setFramerateLimit(FPS);
    sf::Clock clock;
    sf::CircleShape circle(10.0f);
    circle.setOrigin(10.0f, 10.0f);
    circle.setPosition(0, 150.0f);

    sf::Event ev;
    while (window.isOpen())
    {
        //Wait until 1/60th of a second has passed, then update everything.
        if (clock.getElapsedTime().asSeconds() >= 1.0f / FPS)
        {
            redraw = true; //We're ready to redraw everything
            circle.move(1.0f, 0);
            clock.restart();
        }

        //Handle input
        while (window.pollEvent(ev))
        {
            if (ev.type == sf::Event::Closed) window.close();
        }

        //Draw stuff if ready
        if (redraw)
        {
            redraw = false;
            window.clear(sf::Color(0, 0, 0));
            window.draw(circle);
            window.display();
        }
    }

    return 0;

    return(0);
}
