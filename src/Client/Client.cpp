/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(int port)
{
}

rtp::Client::~Client()
{
}

//UDP
void rtp::Client::run()
{
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket{io_context};
    socket.open(boost::asio::ip::udp::v4());

    //temporaire en attendant de savoir comment envoyer un int
    socket.send_to(
    boost::asio::buffer("ACTIONTYPE::CONNECT"),
    boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), 3303});
}
//port 3303