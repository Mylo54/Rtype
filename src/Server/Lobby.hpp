/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server 
*/

#ifndef LOBBY_SERVER_HPP_
#define LOBBY_SERVER_HPP_

#include "Server.hpp"

namespace rtp {
    class Lobby {
        public:
            Lobby(std::string lobbyName = "R-TYPE SERVER");
            ~Lobby();
            
            

        protected:
        private:
            int _lobbyID;
            std::string _lobbyName;
            std::string _roomName;
        
            
    };
};

#endif /* !LOBBY_SERVER_HPP_ */