/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TCPClient
*/

#include "TCPClient.hpp"

rtp::TCPClient::TCPClient()
{
}

rtp::TCPClient::~TCPClient()
{
}

bool rtp::TCPClient::connect(std::string host, std::string service)
{
    boost::asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(host, service);
    boost::system::error_code errors;
    boost::asio::connect(_socket, endpoints, errors);

    if (errors)
        return false;
    return true;
}

void rtp::TCPClient::send(std::string msg)
{
    _socket.send(boost::asio::buffer(msg));
}

std::string rtp::TCPClient::receive()
{
    std::string res;
    std::array<char, 128> buffer;
    boost::system::error_code errors;

    size_t len = _socket.read_some(boost::asio::buffer(buffer), errors);
    res.append(buffer.data(), len);
    return (res);
}
