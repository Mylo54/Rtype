/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystems
*/

#ifndef CLIENTSYSTEMS_HPP_
#define CLIENTSYSTEMS_HPP_

#include "../Engine/Registry.hpp"
#include "../NetworkStructs.hpp"
#include "../Components/Components.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace rtp
{
    class ClientSystems {
        public:
            ClientSystems(std::vector<int> dimWdw, std::string nameWdw, std::string adress, int port,
            boost::asio::ip::udp::socket &socket);
            ~ClientSystems();

            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system 
            void positionSystem(eng::Registry &r);

            /// @brief A system who animate every animatable entity
            /// @param r The Registry on which to apply the system 
            void animateSystem(eng::Registry &r);

            /// @brief A system who draws every drawable entity
            /// @param r The Registry on which to apply the system 
            void drawSystem(eng::Registry &r);

            /// @brief A system who handles inputs and stores actions
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

            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

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

            /// @brief A system which damage enemies colliding a player's bullet
            /// @param r The Registry on which to apply the system
            void playerBullets(eng::Registry &r);

            /// @brief A system which kill dead enemies
            /// @param r The Registry on which to apply the system
            void killDeadEnemies(eng::Registry &r);

            /// @brief A system that lets you know if the window is open
            bool windowOpen();

            /// @brief A system who close the window
            void eventCloseWindow();
        protected:
        private:
            /// @brief A method that gets a synced entity id
            /// @param syncId The synced component id
            /// @return The entity id
            int _getSyncedEntity(eng::Registry &r, int syncId);

            /// @brief A short system which damage an enemy and destroys bullets
            /// @param r The Registry on which to apply the system 
            /// @param b The bullets data
            /// @param p The Position of the bullet
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);

            sf::Event _event;
            sf::RenderWindow _w;
            sf::Clock _c;
            boost::asio::ip::udp::socket &_socket;
            boost::asio::ip::udp::endpoint _endpoint;
    };
} // namespace rtp



#endif /* !CLIENTSYSTEMS_HPP_ */
