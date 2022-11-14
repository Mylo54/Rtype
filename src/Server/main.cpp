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
    /*rtp::TCPServer server(4000);

    server.connect();
    std::cout << "server" << std::endl;
    server.runContext();*/
    //std::string msg = server.receive()[0];
    //std::cout << msg << std::endl;
    rtp::Server s = rtp::Server(4000);
    s.run();
    return (success);
}