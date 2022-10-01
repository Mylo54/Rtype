/*
** EPITECH PROJECT, 2022
** B-CPP-500-NCY-5-1-rtype-clovis.schneider
** File description:
** main of Client
*/

#include "Client.hpp"

rt::Client::Client(int port)
{
    
}

rt::Client::~Client()
{
}

void rt::Client::run()
{
    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket{io_context};
    socket.open(boost::asio::ip::udp::v4());

    socket.send_to(
    boost::asio::buffer("Hello world!"),
    boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), 3303});
}

int main(int argc, char **argv)
{
    try {
        rt::Client cli(55);
        cli.run();
    }
    catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return (0);
}
