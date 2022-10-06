/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port)
{
    
}

rtp::Server::~Server()
{
}

void rtp::Server::run()
{
    boost::asio::io_context io_context;

    for (;;) {
        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303});
        boost::asio::ip::udp::endpoint client;
        char recv_str[1024] = {};
        socket.receive_from(boost::asio::buffer(recv_str), client);
        std::cout << client << ": " << recv_str << '\n';
    }
}

int errorManagement(int ac, char **av)
{
    if (ac != 2)
        return(84);
    for (int i = 0; i < strlen(av[1]); i++) {
        if(!isdigit(av[1][i])) {
            std::cout << "PORT format is not correct according to syntax\n";
            return (84);
        }
    }
    return(0);
}

int main(int ac, char **av)
{
    if (errorManagement(ac, av) == 84) {
        std::cout << "\033[1;31mInvalid Argument Parameters\033[0m\n";
        std::cout << "Usage: ./Server-Rutabaga <PORT>\n";
    }

    try {
        rtp::Server srv(std::atoi(av[1]));
        srv.run();
    }
    catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }

    eng::RegistryManager manage;

    for (int i = 1; i < ac; i++)
        if (strcmp(av[i], "-debug") == 0) {
            manage.setDebugMode(true);
            manage.createLogPath();
        }
    manage.addRegistry("r1");
    eng::Registry &reg = manage.getTop();
    rtp::SystemsServer systems;

    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());

    while (true) {
        systems.positionSystem(reg);
        systems.controlSystem(reg);
        systems.controlMovementSystem(reg);
        systems.controlFireSystem(reg);
        systems.sendData(reg);
        systems.receiveData(reg);
    }

    return (0);
}
