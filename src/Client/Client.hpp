/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../Components/Components.hpp"
#include "../ClientSystems/ClientSystems.hpp"
#include "../Engine/RegistryManager.hpp"
#include "../NetworkStructs.hpp"

namespace rtp {
    class Client {
        public:
            Client(boost::asio::ip::port_type port);
            ~Client();
            void run();
            void systemsLoop();
            void send();

            /// @brief Connect client to server
            /// @return a vector with data
            /// [0]: 0 for success, 1 for failure
            /// [1]: the playerId
            /// [2]: the syncId
            std::vector<int> connect();

            /// @brief Disconnect the client from the server
            void disconnect();

        protected:
        private:
            /// @brief Opens a udp socket
            void _openSocket();

            /// @brief Setup the registry with every sparse array needed
            /// @param r The Registry to setup
            void _setupRegistry(eng::Registry &reg);

            /// @brief Adds a controllable player to a registry
            /// @param reg The Registry on which to adds the player 
            /// @param playerId The player id (1, 2, 3 or 4)
            /// @param syncId The sync component id
            /// @return The entity containing the player
            eng::Entity _addPlayer(eng::Registry &reg, int playerId, int syncId);

            /// @brief Adds an enemy to a registry
            /// @param reg The Registry on which to adds the enemy 
            /// @return The entity containing the enemy
            eng::Entity _addEnemy(eng::Registry &reg);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            /// @return A vector of entities, each representing a background
            std::vector<eng::Entity> _addBackgrounds(eng::Registry &reg);

            /// @brief Add a chatbox to a registry
            /// @param reg The Registry on which to add the backgrounds
            /// @return The entity containing the chatbox
            eng::Entity _addChatBox(eng::Registry &reg);

            eng::RegistryManager _manager;
            int _port;
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socket{_ioContext};

            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::socket _socketTCP;
            boost::system::error_code _error;
    };
}

#endif /* !CLIENT_HPP_ */
