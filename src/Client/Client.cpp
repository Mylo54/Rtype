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

    std::cout << "WAITING TO SEND\n";

    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket{io_context};
    socket.open(boost::asio::ip::udp::v4());

    boost::array<rtp::ACTIONTYPE_INGAME, 1> data_tbs = {DOWN};
    socket.send_to( boost::asio::buffer(data_tbs),
    boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), 3303});
}
//port 3303