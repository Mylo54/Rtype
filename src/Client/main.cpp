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
    srand(time(NULL));
    rtp::Client client(4000 + (rand() % 1000));
    int success = 0;

    success = client.run();
    return (0);
}
