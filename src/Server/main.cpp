/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include "Server.hpp"
#include <iostream>

int main(int argc, char **argv)
{

    int success = 0;
    rtp::Server server(4000);
    /*rtp::UDPServer server(4000);

    while (server.getNumberOfClients() == 0) {
        server.listen();
    }*/
    server.run();
    return (success);
}