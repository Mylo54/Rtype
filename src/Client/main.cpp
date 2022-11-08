/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** main
*/

#include <iostream>
#include "Client.hpp"

int main(int argc, char **argv)
{
    rtp::Client client;
    int success = 0;

    success = client.run();
    return (0);
}
