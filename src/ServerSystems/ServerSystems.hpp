/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystems
*/

#ifndef SERVERSYSTEMS_HPP_
#define SERVERSYSTEMS_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../NetworkStructs.hpp"
#include "../Engine/Registry.hpp"
#include "../Components/Components.hpp"

namespace rtp {
    class ServerSystems {
        public:
            ServerSystems(std::string adress, int port,
            boost::asio::ip::udp::socket &socket);
            ~ServerSystems();

            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system 
            void positionSystem(eng::Registry &r);

            /// @brief A system who handles inputs and stores actions
            /// @param r The Registry on which to apply the system 
            void controlSystem(eng::Registry &r);

            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

            /// @brief A system which sends data to the server
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);
            
            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);
        protected:
        private:
            boost::asio::ip::udp::socket &_socket;
            boost::asio::ip::udp::endpoint _endpoint;
    };
};

#endif /* !SERVERSYSTEMS_HPP_ */
