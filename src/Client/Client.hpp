/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <boost/asio.hpp>
#include <boost/array.hpp>

namespace rtp {

    enum ACTIONTYPE_PREGAME {
        OK,
        KO,
        CONNECT,
        CREATE_LOBBY,
        LIST_LOBBIES,
        JOIN_LOBBY,
        PLAYER_JOINED_LOBBY,
        START_GAME
    };

    enum ACTIONTYPE_INGAME {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        SHOT,
        QUIT
    };

    class Client {
        public:
            Client(int port);
            ~Client();
            void run();
        protected:
        private:
    };
}

#endif /* !CLIENT_HPP_ */
