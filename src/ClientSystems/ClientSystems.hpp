/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystems
*/

#ifndef CLIENTSYSTEMS_HPP_
#define CLIENTSYSTEMS_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../NetworkStructs.hpp"
#include "../Components/Components.hpp"
#include "../Client/PauseMenu.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace rtp
{
    class ClientSystems {
        public:
            //why here?
            enum ChatBoxStyle {
                CHAT,
                EVENT
            };

            /// @brief ClientSystem object constructor
            /// @param w render window of the client
            /// @param c clock of the client
            /// @param delta delta time of the server
            /// @param adress adress of the server
            /// @param port port of the server
            /// @param socket udp socket of the server
            /// @param focus the focus state of the window
            ClientSystems(eng::GraphicSystems &gfx,
            std::string adress, int port, boost::asio::ip::udp::socket &socket,
            eng::SuperInput &inputs);
            ~ClientSystems();

            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system
            void positionSystem(eng::Registry &r);

            /// @brief A system who animate every animatable entity
            /// @param r The Registry on which to apply the system
            void animateSystem(eng::Registry &r);

            /// @brief A system who handles the shooting
            /// @param r The Registry on which to apply the system
            void shootSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

            /// @brief A system who draws the background layers
            /// @param r The Registry on which to apply the system
            void backgroundSystem(eng::Registry &r);

            /// @brief A system who handles inputs and stores actions
            /// @param r The Registry on which to apply the system
            void controlSystem(eng::Registry &r, eng::RegistryManager &manager);

            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

            /// @brief A system who handle button clicking
            /// @param r The registry on which to apply the system
            void buttonSystem(eng::Registry &r, eng::RegistryManager &manager);

            /// @brief A system that logs every loggable component
            /// @param r The Registry on which to apply the system
            void logSystem(eng::Registry &r);

            /// @brief A system that plays every sounds set to play
            /// @param r The Registry on which to apply the system
            void playSoundSystem(eng::Registry &r);

            /// @brief A system that plays every music set to play
            /// @param r The Registry on which to apply the system
            void playMusicSystem(eng::Registry &r);
            
            /// @brief A system which damage enemies colliding a player's bullet
            /// @param r The Registry on which to apply the system
            void playerBullets(eng::Registry &r);

            /// @brief A system which kill dead enemies
            /// @param r The Registry on which to apply the system
            void killDeadEnemies(eng::Registry &r);

            /// @brief A system who handles inputs for chatting
            /// @param r The registry on which to apply the system
            void controlChatSystem(eng::Registry &r);

            /// @brief A system who set a text in a Writable
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            /// @param wrt the targeted Writable
            void setText(eng::Registry &r, std::string message, std::optional<eng::Writable> &wrt,  rtp::ClientSystems::ChatBoxStyle style);

            /// @brief A system who set a text in a Writable
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            /// @param name the name of the targeted Writable
            void setText(eng::Registry &r, std::string message, std::string name,  rtp::ClientSystems::ChatBoxStyle style);

            /// @brief Write a message in the chat box
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            void writeInChatBox(eng::Registry &r, std::string message, rtp::ClientSystems::ChatBoxStyle style);

            /// @brief Create a bottom chatBox line
            /// @param reg The registry on which to apply the system
            void addChatBox(eng::Registry &reg);

            /// @brief Prevents player from going out of the window and limit its velocity
            /// @param reg The registry on which to apply the system
            void limitPlayer(eng::Registry &reg);

            /// @brief Kill bullets that are offscreen
            /// @param r The registry on which to apply the system
            void killBullets(eng::Registry &r);

            /// @brief A system who set the state of a button according
            /// @param r The Registry on which to apply the system
            void buttonStateSystem(eng::Registry &r);

            /// @brief Kill entities that are offscreen
            /// @param r The registry on which to apply the system
            void killOutOfBounds(eng::Registry &r);
        protected:
        private:
            /// @brief A short system which damage an enemy and destroys bullets
            /// @param r The Registry on which to apply the system
            /// @param b The bullets data
            /// @param p The Position of the bullet
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);

            /// @brief Client score
            int _score = 0;

            /// @brief The renderWindow of the client
            sf::RenderWindow &_w;
            /// @brief The clock off the server
            sf::Clock &_c;
            /// @brief The delta time of the server
            sf::Time &_delta;
            bool &_isWindowFocused;
            bool _isButtonRelease;
            bool _isEscapeRelease;
            eng::GraphicSystems &_gfx;
            eng::SuperInput &_inputs;
    };
} // namespace rtp



#endif /* !CLIENTSYSTEMS_HPP_ */
