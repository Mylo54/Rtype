/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include "AScene.hpp"

namespace rtp
{
    class Settings : public AScene{
        public:
            Settings(scene_package_t pack, sf::Color c);
            ~Settings();

            void setupRegistry() override;
            void systemRun() override;
            sf::Color color;
        protected:
        private:
    };
} // namespace rtp

#endif /* !SETTINGS_HPP_ */
