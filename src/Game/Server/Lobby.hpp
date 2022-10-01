/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server 
*/

#ifndef LOBBY_SERVER_HPP_
#define LOBBY_SERVER_HPP_

#include "Server.hpp"

namespace rt {
    class Lobby {
        public:
            Lobby();
            ~Lobby();
            
            

        protected:
        private:
            int _lobbyID;
            std::string _roomName;
        
            
    };
};

#endif /* !LOBBY_SERVER_HPP_ */