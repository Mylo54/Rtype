/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** GraphicsSystems
*/

#ifndef GRAPHICSSYSTEMS_HPP_
#define GRAPHICSSYSTEMS_HPP_

#include "../Components/Components.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp
{
    class GraphicsSystems {
        public:
            /// @brief GraphicsSystems object constructor
            /// @param dimWdw 
            /// @param nameWdw 
            GraphicsSystems(std::vector<int> dimWdw, std::string nameWdw);
            ~GraphicsSystems();

            /// @brief A system who draws every drawable entity
            /// @param r The Registry on which to apply the system
            void drawSystem(eng::Registry &r);

            /// @brief A system who write every writable entity
            /// @param r The Registry on which to apply the system
            void writeSystem(eng::Registry &r);

            /// @brief A system who displays the screen
            /// @param r The Registry on which to apply the system
            void displaySystem(eng::Registry &r);

            /// @brief A system who draws the background layers
            /// @param r The Registry on which to apply the system
            void backgroundSystem(eng::Registry &r);

            /// @brief A system who animate every animatable entity
            /// @param r The Registry on which to apply the system
            void animateSystem(eng::Registry &r);

            /// @brief A system that lets you know if the window is open
            /// @return true if open, false if closed
            bool windowOpen();

            /// @brief A system who handles inputs and stores actions
            /// @param r The Registry on which to apply the system
            void controlSystem(eng::Registry &r);

            /// @brief A system who handle specific window event like closing or focus
            void eventCatchWindow();

            /// @brief A system who clears the screen
            void clearSystem();

            /// @brief Set the max frame rate of the _w attribut
            /// @param mfr new maximum frame rate (O to disable max limit)
            void setMaxFrameRate(unsigned int mfr);

            /// @brief get the window in the graphics system
            /// @return a reference to the sf::RenderWindow
            sf::RenderWindow &getWindow();

            /// @brief get the clock in the graphics system
            /// @return a reference to the sf::Clock
            sf::Clock &getClock();

            /// @brief get the delta in the graphics system
            /// @return a reference to the sf::Time delta
            sf::Time &getDelta();

            /// @brief A system who displays the screen
            /// @param r The Registry on which to apply the system
            void displaySystem();

            /// @brief A system who set the state of a button according
            /// @param r The Registry on which to apply the system
            void buttonStateSystem(eng::Registry &r);

            /// @brief Update the delta time
            void updDeltaTime();
        protected:
        private:
            sf::RenderWindow _w;
            sf::Event _event;
            sf::Clock _c;
            sf::Time _delta;
            bool _isWindowFocused = true;
    };
} // namespace rtp



#endif /* !GRAPHICSSYSTEMS_HPP_ */
