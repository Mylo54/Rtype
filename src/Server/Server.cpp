/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server()
{
}

rtp::Server::~Server()
{
}

void rtp::Server::run()
{
    std::cout << "Server is up!" << std::endl;

    // Wait for request

    // On TCP request, either
    //  CreateRoomRequest:
    //  -   create a thread with a room
    //  JoinRoomRequest:
    //  -   redirect the player into a room
}