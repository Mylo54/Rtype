/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkStructs
*/

#ifndef NETWORKSTRUCTS_HPP_
#define NETWORKSTRUCTS_HPP_

#include <iostream>
#include <any>

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
        QUIT,
        SYNCHRONISATION,
        END_PACKET
    };

    enum COMPONENTS_SYNCED {
        POSITION,
        VELOCITY,
        ENEMY_STATS,
        PLAYER_STATS
    };

    typedef struct payload {
        int ACTION_NAME;
        size_t bodySize = 0;
        void * body = NULL;
    } networkPayload;

    typedef struct synced_elem {
        int COMPONENT_NAME;
        size_t id;
        std::any body;
    } synced_component;

    typedef struct connectPayload_s {
        int ACTION_NAME;
        int playerId;
        int syncId;
    } connectPayload_t;

    typedef struct inputPayload_s {
        int ACTION_NAME;
        int syncId;
    } inputPayload_t;
} // namespace rtp


#endif /* !NETWORKSTRUCTS_HPP_ */
