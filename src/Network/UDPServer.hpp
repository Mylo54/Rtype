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

            void send(std::vector<int> &data, int to);
            void sendToAll(std::vector<int> &data);

            std::vector<int> receive();

            void addEndpoint(std::string address, int port);
            void removeEndpoint(std::string address, int port);
        protected:
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::endpoint _endpoint;
            boost::asio::ip::udp::socket _socket;

            std::vector<boost::asio::ip::udp::endpoint> _endpoints;
    };
} // namespace rtp


#endif /* !UDPSERVER_HPP_ */
