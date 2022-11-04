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
#include "../ClientSystems/NetworkSystems.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../NetworkStructs.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"
#include "PauseMenu.hpp"

namespace rtp {
    class Client {
        public:
            /// @brief Client object constructor
            /// @param port Port of connection to the server
            Client(boost::asio::ip::port_type &port, std::string &portStr, std::string &serverAddr, int socketUdpPort);
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
            int connect(eng::RegistryManager &manager, bool multiplayer, int lvl);
            

            /// @brief Disconnect the client from the server
            void disconnect();

            void dataReception();
            void dataSend();

            
        protected:
        private:
            /// @brief Fill the structure sent to the server countaining the client adress
            /// @param address The client adress
            /// @return The filled structure
            /*boost::array<demandConnectPayload_s, 1> _fillDataToSend(std::string address);*/

            /// @brief Sets up the differents actions & events for the game
            void _setupInputs();

            int _mySyncId = 0;
            int _myPlayerId = 0;

            eng::RegistryManager _manager;
            int _port;
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socket{_ioContext};

            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::socket _socketTCP;
            boost::system::error_code _error;
            rtp::NetworkSystems _net;
            eng::GraphicSystems _gfx;

            std::string _serverAddr;
            std::string _portStr;
            eng::SuperInput _inputs;
            eng::TextureManager _textureManager;

            std::thread _receiveData;
            std::thread _sendData;

    };
}

#endif /* !CLIENT_HPP_ */
