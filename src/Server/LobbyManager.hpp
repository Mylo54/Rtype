/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server 
*/

#ifndef LOBBY_MANAGER_SERVER_HPP_
#define LOBBY_MANAGER_SERVER_HPP_
#include "Lobby.hpp"
#include <list>
#include <iterator>
#include <iostream>

namespace rtp {
    class LobbyManager {
        public:
            LobbyManager();
            ~LobbyManager();

            /// @brief get the number of lobby in the list
            /// @return int
            int getNumberLobby();

            /// @brief add lobby at the end of the list
            /// @return void
            void addLobby(rtp::Lobby lobby);

            /// @brief remove lobby in the list depending on his position
            /// @return void
            void removeLobby(int position);

        protected:
        private:
            std::list<rtp::Lobby> _listLobby;
            
    };
};

#endif /* !LOBBY_MANAGER_SERVER_HPP_ */