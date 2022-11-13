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
    rtp::TCPServer server(4000);
    int success = 0;

    server.connect();
    std::cout << "server" << std::endl;
    server.runContext();
    //std::string msg = server.receive()[0];
    //std::cout << msg << std::endl;
    while(1);
    return (success);
}