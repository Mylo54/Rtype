/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "Client.hpp"

int main(int argc, char **argv)
{
    srand(time(NULL));
    boost::asio::ip::port_type port = (rand() % 1000) + 3000;
    rtp::Client client(port);

    client.run();
    return 0;
}