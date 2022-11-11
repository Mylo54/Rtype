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
            Network(int port);
            ~Network();

            /// @brief Sends the data in UDP to all endpoints
            /// @param data the data 
            void UDPsendData(std::vector<int> &data);

            /// @brief Sends the data in UDP to the endpoint at to's id
            /// @param data the data 
            /// @param to id of the endpoint in the endpoints vector
            void UDPsendDataTo(std::vector<int> &data, int to);

            /// @brief Receive the data on the udp socket
            /// @return a vector of ints (the data)
            /// @warning this function blocks until some data is received
            std::vector<int> UDPreceiveData();

            /// @brief removes an udp endpoint with the id
            /// @param id the index in the endpoints vector
            void UDPremoveEndpoint(int id);

            /// @brief removes an udp endpoint whoses parameters matches:
            /// @param address the address of the endpoint
            /// @param port the port of the endpoint
            void UDPremoveEndpoint(std::string address, int port);

            /// @brief Sends the data in TCP to all endpoints
            /// @param data the data
            void TCPsendData(std::string data);

            /// @brief Sends the data in TCP to all endpoints
            /// @param data the data
            /// @param to id of the endpooint in the endpoints vector
            void TCPsendDataTo(std::string data, int to);

            /// @brief receive the data from 'id' in sockets vector
            /// @param from the id of the socket in the sockets vector
            std::string TCPreceiveDataFrom(int from);

            std::string TCPreadData();
            
            void TCPwriteData(std::string data);

            /// @brief adds an endpoint to the vector of tcp endpoints
            /// @param address the address of the endpoint
            /// @param port the port of the endpoint
            /// @warning this method does not verify if the endpoint is valid
            void UDPaddEndpoint(std::string address, int port);

            /// @brief adds an endpoint to the vector of tcp endpoints
            /// @param address the address of the endpoint
            /// @param port the port of the endpoint
            /// @warning this method does not verify if the endpoint is valid
            void TCPaddEndpoint(std::string address, int port);

            /// @brief Connect client to server
            /// @return 0 if connect succesfuly, 1 if failed
            int connectionToServer(bool multiplayer, int lvl, int port);

            /// @brief fct bloquante connection between server and client
            void runConnectToClient();

            /// @brief fonction for server to connect to the client
            /// @return void
            void connectToClient();

            /// @brief connects a tcp socket to a host:service via a resolver
            /// @param host localhost/127.0.0.1/0.0.0.0/etc...
            /// @param service the 'port' or service name to port
            /// @return true on success, false on failure
            bool connect(std::string host, std::string service);

            /// @brief listen to connections
            void listen();


        protected:
            /// @brief send and receive info after TCP connection to the server
            /// @return 0 if connect succesfuly, 1 if failed
            int _sendAfterConnectToServer(bool multiplayer, int lvl, int port);

            /// @brief Execute when connection is established : confirm client connection
            /// @param sckt : client socket
            boost::array<rtp::demandConnectPayload_s, 1> _afterConnectionToClient(boost::asio::ip::tcp::socket sckt);

        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socketUDP;
            boost::asio::ip::tcp::socket _socketTCP{_ioContext};
            boost::asio::ip::tcp::acceptor _acceptor;

            boost::asio::ip::tcp::socket _waitingSocket{_ioContext};
            std::vector<boost::asio::ip::udp::endpoint> _UDPendpoints;
            std::optional<boost::asio::ip::tcp::socket> _socketOptional;
            std::vector<boost::asio::ip::tcp::socket *> _socketList;
            // boost::asio::ip::tcp::acceptor _acceptor;
            int _mySyncId = 0;//utile ?
            int _myPlayerId = 0;//utile ?

            std::thread _connectToClient;
    };
} // namespace rtp

#endif /* !NETWORK_HPP_ */
