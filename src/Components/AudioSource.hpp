/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** AudioSource
*/

#ifndef AUDIOSOURCE_HPP_
#define AUDIOSOURCE_HPP_

#include <SFML/Audio.hpp>

namespace rtp
{
    class AudioSource {
        public:
            AudioSource(std::string filepath, bool pToPlay = false) {
                toPlay = pToPlay;
                buffer->loadFromFile(filepath);
                sound.setBuffer(*buffer);
            }
            ~AudioSource() {}

            sf::SoundBuffer *buffer = new sf::SoundBuffer;
            sf::Sound sound;
            bool toPlay;
        protected:
        private:
    };
} // namespace rtp



#endif /* !AUDIOSOURCE_HPP_ */
