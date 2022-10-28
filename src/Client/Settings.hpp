/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Settings
*/

#ifndef SETTINGS_HPP_
#define SETTINGS_HPP_

#include <iostream>
#include <fstream>
#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp {
    class Settings {
        public:
            Settings(eng::RegistryManager &manager);
            ~Settings();

        protected:
        private:
    };
}

#endif /* !SETTINGS_HPP_ */
