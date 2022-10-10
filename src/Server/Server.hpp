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
#include "../ServerSystems/ServerSystems.hpp"
#include "../Engine/RegistryManager.hpp"

namespace rtp {
    class Server {
        public:
            Server(int port);
            ~Server();

            void run();
            void requestConnection();
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
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::endpoint _client;
            boost::asio::ip::udp::socket _socket;
            boost::array<networkPayload, 1> _dataRec;
            boost::asio::ip::tcp::acceptor _acceptor;
            boost::asio::io_service _ioService;
    };
};

#endif /* !SERVER_HPP_ */
