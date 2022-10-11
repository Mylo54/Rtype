/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkStructs
*/

#ifndef NETWORKSTRUCTS_HPP_
#define NETWORKSTRUCTS_HPP_

#include <iostream>


// Yeah so this is kinda bad...
namespace rtp
{
    enum ACTIONTYPE_PREGAME {
        OK,
        KO,
        CONNECT,
        CREATE_LOBBY,
        LIST_LOBBIES,
        JOIN_LOBBY,
        PLAYER_JOINED_LOBBY,
        START_GAME,
        LEAVE_GAME
    };

    enum ACTIONTYPE_INGAME {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        SHOT,
        QUIT
    };

    typedef struct payload {
        int ACTION_NAME;
        size_t bodySize = 0;
        void * body = NULL;
    } networkPayload;
} // namespace rtp


#endif /* !NETWORKSTRUCTS_HPP_ */
