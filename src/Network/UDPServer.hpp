/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UDPServer
*/

#ifndef UDPSERVER_HPP_
#define UDPSERVER_HPP_

#include <boost/asio.hpp>
#include <vector>

namespace rtp
{
    class UDPServer {
        public:
            UDPServer(int port);
            ~UDPServer();

            /// @brief Sends data to a stored endpoint
            /// @param data a vector of ints
            /// @param to id of endpoint in the endpoint list
            void send(std::vector<int> &data, int to);

            /// @brief Sends data to all stored endpoint
            /// @param data a vector of ints
            void sendToAll(std::vector<int> &data);

            /// @brief receives data in the socket
            /// @return a vector of ints (the data)
            std::vector<int> receive();

            /// @brief receives data in the socket and stores sender endpoint
            /// @return a vector of ints (the data)
            std::vector<int> listen();

            /// @brief adds an endpoint to the endpoints list
            /// @param address the address
            /// @param port the port
            void addEndpoint(std::string address, int port);

            /// @brief removes an endpoint to the endpoints list
            /// @param address the address
            /// @param port the port
            void removeEndpoint(std::string address, int port);

            int &getNumberOfClients();
        protected:
        private:
            int _numberOfClients = 0;
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::endpoint _endpoint;
            boost::asio::ip::udp::socket _socket;
            std::vector<boost::asio::ip::udp::endpoint> _endpoints;
    };
} // namespace rtp


#endif /* !UDPSERVER_HPP_ */
