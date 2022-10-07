/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server 
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <locale>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <string.h>

#include "Lobby.hpp"
#include "../Components/Components.hpp"
#include "../ServerSystems/SystemsServer.hpp"
#include "../Engine/Registry.hpp"
#include "../Engine/IRegistry.hpp"
#include "../Engine/RegistryManager.hpp"

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

    typedef struct payload {
        int ACTION_NAME;
        size_t bodySize = 0;
        void * body = NULL;
    } networkPayload;

    class Server {
        public:
            Server(int port);
            ~Server();

            void run();
            bool isConnected();

            /// @brief get the number of lobby in the list
            /// @return int
            int getNumberLobby();

            /// @brief add lobby at the end of the list
            /// @return void
            void addLobby(rtp::Lobby lobby);

            /// @brief remove lobby in the list depending on his position
            /// @return void
            void removeLobby(int position);
    
            // Liste des méthodes à implémenter :


        protected:
        private:
            bool _connect;
            int _clientPort;
            std::list<rtp::Lobby> _listLobby;
            
    };
};

#endif /* !SERVER_HPP_ */
