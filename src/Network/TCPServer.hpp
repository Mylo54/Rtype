/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** TCPServer
*/

#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <iostream>
#include <thread>
#include <optional>


namespace rtp
{
    class TCPServer {
        public:
            TCPServer(int port);
            ~TCPServer();

            bool connect();

            void send(std::string msg);
            
            std::vector<std::string> receive();

            void runContext();

            std::string receiveFrom(int i);
        protected:
            void _blockFct();
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::tcp::socket _socketTCP{_ioContext};
            boost::asio::ip::tcp::acceptor _acceptor;
            boost::asio::ip::tcp::socket _waitingSocket{_ioContext};
            std::vector<boost::asio::ip::tcp::socket *> _socketList;
            std::thread _runContext;
            std::optional<boost::asio::ip::tcp::socket> _socketOptional;
    };
}

#endif /* !TCPSERVER_HPP_ */
