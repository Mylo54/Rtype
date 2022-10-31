/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkSystems
*/

#ifndef NETWORKSYSTEMS_HPP_
#define NETWORKSYSTEMS_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Components/Components.hpp"
#include "../NetworkStructs.hpp"
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "ClientSystems.hpp"
#include <iostream>
#include "../NetworkStructs.hpp"
#include <cmath>

namespace rtp
{
    class NetworkSystems {
        public:
            enum ChatBoxStyle {
                CHAT,
                EVENT
            };

            /// @brief NetworkSystems object constructor
            /// @param address adress of the server
            /// @param port port of the server
            /// @param socket udp socket of the client
            /// @param mySyncId synchronisation id of the player
            NetworkSystems(std::string address, int port,
            boost::asio::ip::udp::socket &socket, sf::Time &delta);
            ~NetworkSystems();

            /// @brief A system which sends data to the server
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);

            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void oldReceiveData(eng::Registry &r);

            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);

            void disconnectSystems(eng::Registry &r);

            /// @brief A system who set a text in a Writable
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            /// @param wrt the targeted Writable
            void setText(eng::Registry &r, std::string message, std::optional<eng::Writable> &wrt,  rtp::NetworkSystems::ChatBoxStyle style);

            /// @brief A system who set a text in a Writable
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            /// @param name the name of the targeted Writable
            void setText(eng::Registry &r, std::string message, std::string name,  rtp::NetworkSystems::ChatBoxStyle style);

            /// @brief Write a message in the chat box
            /// @param r The registry on which to apply the system
            /// @param message The new text to display
            void writeInChatBox(eng::Registry &r, std::string message, rtp::NetworkSystems::ChatBoxStyle style);

            /// @brief Create a bottom chatBox line
            /// @param reg The registry on which to apply the system
            void addChatBox(eng::Registry &reg);

            std::vector<int> connect(int port);

            void setSyncId(int id);

            void setDelta(sf::Time &delta);
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

            /// @brief Completes a Bonus entity received by the server
            /// @param r The registry containing the entity
            /// @param e The id of the entity
            void _completeBonus(eng::Registry &r, int e);

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

            sf::Time &_delta;
    };
} // namespace rtp



#endif /* !NETWORKSYSTEMS_HPP_ */
