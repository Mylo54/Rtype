/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TCPClient
*/

#ifndef TCPCLIENT_HPP_
#define TCPCLIENT_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace rtp
{
    class TCPClient {
        public:
            TCPClient();
            ~TCPClient();

            bool connect(std::string host, std::string service);

            void send(std::string msg);
            
            std::string receive();
        protected:
        private:
            boost::asio::io_context _ioContext;
            boost::asio::ip::tcp::resolver resolver{_ioContext};
            boost::asio::ip::tcp::socket _socket{_ioContext};
    };
} // namespace rtp

#endif /* !TCPCLIENT_HPP_ */
