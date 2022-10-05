/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Systems
*/

#ifndef SYSTEMS_HPP_
#define SYSTEMS_HPP_

#include "../Engine/Registry.hpp"
#include "../Components/Components.hpp"

namespace rtp
{
    class Systems {
        public:
            Systems(sf::RenderWindow &w, sf::Clock &c);
            ~Systems();

            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system 
            void positionSystem(eng::Registry &r);

            /// @brief A system who draws every drawable entity
            /// @param r The Registry on which to apply the system 
            void drawSystem(eng::Registry &r);

            /// @brief A system who handle controllable entities
            /// @param r The Registry on which to apply the system 
            void controlSystem(eng::Registry &r);

            /// @brief A system who clears the screen
            /// @param r The Registry on which to apply the system
            void clearSystem(eng::Registry &r);

            /// @brief A system who handles the shooting
            /// @param r The Registry on which to apply the system
            void shootSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

            /// @brief A system who displays the screen
            /// @param r The Registry on which to apply the system
            void displaySystem(eng::Registry &r);

            /// @brief A system who draws the background layers
            /// @param r The Registry on which to apply the system
            void backgroundSystem(eng::Registry &r);

            /// @brief A system that logs every loggable component
            /// @param r The Registry on which to apply the system 
            void logSystem(eng::Registry &r);

            /// @brief A system that plays every sounds set to play
            /// @param r The Registry on which to apply the system
            void playSoundSystem(eng::Registry &r);

            /// @brief A system which sends data to the server
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);
            
            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);
        protected:
        private:
            sf::RenderWindow &_w;
            sf::Clock &_c;
    };
} // namespace rtp



#endif /* !SYSTEMS_HPP_ */
