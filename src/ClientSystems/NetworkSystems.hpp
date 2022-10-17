/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkSystems
*/

#ifndef NETWORKSYSTEMS_HPP_
#define NETWORKSYSTEMS_HPP_

#include "../Engine/Registry.hpp"
#include "../Components/Components.hpp"
#include "../NetworkStructs.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "ClientSystems.hpp"

namespace rtp
{
    class NetworkSystems {
        public:
            NetworkSystems(std::string address, int port,
            boost::asio::ip::udp::socket &socket, int mySyncId);
            ~NetworkSystems();

            /// @brief A system which sends data to the server
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);

            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);

            void disconnectSystems(eng::Registry &r);
        protected:
        private:
            /// @brief A method that gets a synced entity id
            /// @param syncId The synced component id
            /// @return The entity id
            int _getSyncedEntity(eng::Registry &r, int syncId);

            /// @brief Completes an enemy entity received by the server
            /// @param r The registry containing the entity
            /// @param e The id of the entity
            void _completeEnemy(eng::Registry &r, int e);

            /// @brief Completes a player entity received by the server
            /// @param r The registry containing the entity
            /// @param e The id of the entity
            void _completePlayer(eng::Registry &r, int e);

            /// @brief The socket of the client
            boost::asio::ip::udp::socket &_socket;

            /// @brief The endpoint where we send data
            boost::asio::ip::udp::endpoint _endpoint;

            /// @brief Container for received data
            boost::array<server_payload_t ,1> _dataBuffer;

            /// @brief The sync id corresponding to the client character
            int _mySyncId;
    };
} // namespace rtp



#endif /* !NETWORKSYSTEMS_HPP_ */
