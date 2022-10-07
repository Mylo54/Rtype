/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port)
{
    this->_connect = false;
    this->_clientPort = 0;
}

rtp::Server::~Server()
{
}

bool rtp::Server::isConnected()
{
    return this->_connect;
}

void rtp::Server::run()
{
    boost::asio::io_context io_context;

    for (;;) {
        std::cout << "WAITING TO RECEIVE\n";
        


        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303});
        boost::asio::ip::udp::endpoint client;


        boost::array<rtp::ACTIONTYPE_INGAME, 1> data_rec;



        size_t len = socket.receive_from(boost::asio::buffer(data_rec), client);
        std::cout << client << " sent us (" << len << "bytes): " << data_rec.at(0) << '\n';
        this->_clientPort = client.port();
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

    //sert à rien pour l'instant cf l.29
    eng::RegistryManager manage;

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
