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
#include "../ClientSystems/GraphicsSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include "../Engine/RegistryManager.hpp"
#include "../NetworkStructs.hpp"

namespace rtp {
    class Client {
        public:
            /// @brief Client object constructor
            /// @param port Port of connection to the server
            Client(boost::asio::ip::port_type port, std::string &serverAddr);
            ~Client();

            /// @brief Run the client
            void run();

            /// @brief The main loop of the client (using systems)
            void systemsLoop();

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
            /// @brief Setup the registry with every sparse array needed
            /// @param r The Registry to setup
            void _setupRegistry(eng::Registry &reg);

            /// @brief Adds a music to the registry
            /// @param reg the registry on which to add the music
            /// @param filepath the filepath on where to find the music
            void _addMusic(eng::Registry &reg, std::string filepath);

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
            void _addBackgrounds(eng::Registry &reg);

            /// @brief Add a text on the screen to display the score
            /// @param reg The registry on which to add the text
            void _addScore(eng::Registry &reg);

            /// @brief Fill the structure sent to the server countaining the client adress
            /// @param address The client adress
            /// @return The filled structure
            boost::array<demandConnectPayload_s, 1> _fillDataToSend(std::string address);

            int _mySyncId = 0;
            int _myPlayerId = 0;

            eng::RegistryManager _manager;
            int _port;
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socket{_ioContext};

            boost::asio::ip::tcp::socket _socketTCP;
            boost::system::error_code _error;

            std::string _serverAddr;
    };
}

#endif /* !CLIENT_HPP_ */
