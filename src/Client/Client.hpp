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
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../NetworkStructs.hpp"
#include "Game.hpp"
#include "MainMenu.hpp"

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
            int connect(eng::RegistryManager &manager);
            

            /// @brief Disconnect the client from the server
            void disconnect();
            
        protected:
        private:
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
            rtp::NetworkSystems _net;
            rtp::GraphicsSystems _gfx;
            
            std::string _serverAddr;
    };
}

#endif /* !CLIENT_HPP_ */
