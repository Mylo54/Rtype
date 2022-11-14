/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** TCPClient
*/

#include "TCPClient.hpp"
#include <iostream>
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

    if (errors) {
        std::cout << "echec connection" << std::endl;
        return false;
    }
    std::cout << "connect" << std::endl;
    return true;
}

void rtp::TCPClient::send(std::string msg)
{
    _socket.send(boost::asio::buffer(msg));
}

std::string rtp::TCPClient::receive()
{
    std::string res;
    std::array<char, 1> numBuf;
    std::vector<char> buf;

    // get msg size
    while (true) {
        boost::asio::read(_socket, boost::asio::buffer(numBuf));
        if (numBuf[0] == ':')   // end of size header
            break;
        res.append(1, numBuf[0]);
    }
    buf.resize(atoi(res.c_str()));

    // get msg
    boost::asio::read(_socket, boost::asio::buffer(buf));
    res.clear();
    res.append(buf.data());
    return (res);
}
