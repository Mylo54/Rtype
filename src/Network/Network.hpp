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

        protected:
            /// @brief send and receive info after TCP connection to the server
            /// @return 0 if connect succesfuly, 1 if failed
            int _sendAfterConnectToServer(bool multiplayer, int lvl, int port);
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socketUDP{_ioContext};
            boost::asio::ip::tcp::socket _socketTCP;

            int _mySyncId = 0;//utile ?
            int _myPlayerId = 0;//utile ?
    };
} // namespace rtp

#endif /* !NETWORK_HPP_ */
