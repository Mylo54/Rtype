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
    if (argc != 3) {
        std::cout << "./Client-Rtype <host> <service/port>" << std::endl;
        return (84);
    }
    srand(time(NULL));
    rtp::Client client(4000 + (rand() % 1000));
    int success = 0;

    //client.connect(argv[1], argv[2]);
    //std::cout << client.listLobbies() << std::endl;
    success = client.run();
    return (success);
}
