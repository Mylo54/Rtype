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

namespace rtp {

    enum ACTIONTYPE {
        OK,
        KO,
        CONNECT,
        CREATE_LOBBY,
        LIST_LOBBIES,
        JOIN_LOBBY,
        PLAYER_JOINED_LOBBY,
        START_GAME
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
