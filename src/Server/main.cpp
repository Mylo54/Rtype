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
    rtp::Server server(4000);
    int success = 0;

    server.init();
    success = server.run();
    return (success);
}