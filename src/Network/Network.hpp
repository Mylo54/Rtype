/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Network
*/

#ifndef NETWORK_HPP_
#define NETWORK_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <optional>
#include "NetworkStructs.hpp"

namespace rtp
{
    class Network {
        public:
            Network();
            ~Network();

            /// @brief Connect client to server
            /// @return 0 if connect succesfuly, 1 if failed
            int connectionToServer(bool multiplayer, int lvl, int port);

            /// @brief fct bloquante connection between server and client
            void runConnectToClient();

            /// @brief fonction for server to connect to the client
            /// @return void
            void connectToClient();

        protected:
            /// @brief send and receive info after TCP connection to the server
            /// @return 0 if connect succesfuly, 1 if failed
            int _sendAfterConnectToServer(bool multiplayer, int lvl, int port);

            /// @brief Execute when connection is established : confirm client connection
            /// @param sckt : client socket
            boost::array<rtp::demandConnectPayload_s, 1> _afterConnectionToClient(boost::asio::ip::tcp::socket sckt);

            void _addEndpoint(std::string address, int port);
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socketUDP{_ioContext};
            boost::asio::ip::tcp::socket _socketTCP{_ioContext};

            std::vector<std::vector<int>> _listDataRec;
            std::vector<boost::asio::ip::udp::endpoint> _endpoints;
            std::optional<boost::asio::ip::tcp::socket> _socketOptional;
            std::vector<boost::asio::ip::tcp::socket *> _socketList;
            int _mySyncId = 0;//utile ?
            int _myPlayerId = 0;//utile ?
    };
} // namespace rtp

#endif /* !NETWORK_HPP_ */
