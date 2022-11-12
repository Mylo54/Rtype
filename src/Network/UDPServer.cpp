/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UDPServer
*/

#include "UDPServer.hpp"

rtp::UDPServer::UDPServer(int port):
_endpoint(boost::asio::ip::udp::v4(), static_cast<boost::asio::ip::port_type>(port)),
_socket(_ioContext, _endpoint)
{
}

rtp::UDPServer::~UDPServer()
{
}

void rtp::UDPServer::send(std::vector<int> &data, int to)
{
    _socket.send_to(boost::asio::buffer(data), _endpoints[to]);
}

void rtp::UDPServer::sendToAll(std::vector<int> &data)
{
    for (int i = 0; i < _endpoints.size(); i++)
        _socket.send_to(boost::asio::buffer(data), _endpoints[i]);
}

std::vector<int> rtp::UDPServer::receive()
{
    std::vector<int> res;

    _socket.wait(boost::asio::socket_base::wait_read);
    res.resize(_socket.available());
    _socket.receive(boost::asio::buffer(res));
    return (res);
}

void rtp::UDPServer::addEndpoint(std::string address, int port)
{
    _endpoints.push_back({
        boost::asio::ip::make_address(address),
        static_cast<boost::asio::ip::port_type>(port)
    });
}

void rtp::UDPServer::removeEndpoint(std::string address, int port)
{
    for (int i = 0; i < _endpoints.size(); i++) {
        auto &current = _endpoints[i];

        if (current.address() == boost::asio::ip::make_address(address)
        && current.port() == static_cast<boost::asio::ip::port_type>(port)) {
            _endpoints.erase(_endpoints.begin() + i);
            return;
        }
    }
}

