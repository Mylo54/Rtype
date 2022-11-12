/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UDPClient
*/

#ifndef UDPCLIENT_HPP_
#define UDPCLIENT_HPP_

#include <boost/asio.hpp>
#include <vector>

namespace rtp
{
    class UDPClient {
        public:
            UDPClient(int port);
            ~UDPClient();

            bool connect(std::string host, std::string service);
            void send(std::vector<int> &data);
            std::vector<int> receive();
        protected:
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::endpoint _endpoint;
            boost::asio::ip::udp::socket _socket;
            boost::asio::ip::udp::endpoint _receiver;
    };
} // namespace rtp




#endif /* !UDPCLIENT_HPP_ */
