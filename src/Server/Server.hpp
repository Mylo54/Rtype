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
#include <string.h>

#include "../Components/Components.hpp"
#include "../SystemsServer/SystemsServer.hpp"
#include "../Engine/Registry.hpp"
#include "../Engine/IRegistry.hpp"
#include "../Engine/RegistryManager.hpp"

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

    class Server {
        public:
            Server(int port);
            ~Server();

            void run();
            bool isConnected();

            // Liste des méthodes à implémenter :


        protected:
        private:
            bool _connect;
            int _clientPort;
            
    };
};

#endif /* !SERVER_HPP_ */
