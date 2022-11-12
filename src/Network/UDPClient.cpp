/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** UDPClient
*/

#include "UDPClient.hpp"

rtp::UDPClient::UDPClient(int port):
_endpoint(boost::asio::ip::udp::v4(), static_cast<boost::asio::ip::port_type>(port)),
_socket(_ioContext, _endpoint)
{
}

rtp::UDPClient::~UDPClient()
{
}

bool rtp::UDPClient::connect(std::string host, std::string service)
{
    _receiver(boost::asio::ip::make_address(host))
    return true;
}

void rtp::UDPClient::send(std::vector<int> &data)
{
    _socket.send_to(boost::asio::buffer(data), _receiver);
}

std::vector<int> rtp::UDPClient::receive()
{
    std::vector<int> buffer;

    _socket.wait(boost::asio::socket_base::wait_type::wait_read);
    buffer.resize(_socket.available());
    _socket.receive(boost::asio::buffer(buffer));
    return (buffer);
}
