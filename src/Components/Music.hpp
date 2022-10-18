/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Music
*/

#ifndef MUSIC_HPP_
#define MUSIC_HPP_

#include <iostream>
#include <SFML/Audio.hpp>

namespace rtp
{
    class Music {
        public:
            Music(std::string filepath, bool toPlay_):toPlay(toPlay_)
            {
                music->openFromFile(filepath);
                music->setVolume(50);
            }
            ~Music() {}

            sf::Music *music = new sf::Music();
            bool toPlay;
        protected:
        private:
    };
} // namespace rtp



#endif /* !MUSIC_HPP_ */
