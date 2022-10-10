/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** mainServer
*/


#include "Server.hpp"

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
    try {
        boost::asio::ip::port_type port(3033);
        rtp::Server srv(port);
        srv.run();
    }
    catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }

    //sert à rien pour l'instant cf l.29
    eng::RegistryManager manage;

    manage.addRegistry("r1");
    eng::Registry &reg = manage.getTop();

    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());

    return (0);
}
