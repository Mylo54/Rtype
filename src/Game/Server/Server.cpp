/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rt::Server::Server(int port)
{
    
}

rt::Server::~Server()
{
}

void rt::Server::run()
{
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
    rt::Server srv(std::atoi(av[1]));
    try {
        srv.run();
    } catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return (0);
}
