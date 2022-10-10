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
#include <functional>
#include <fstream>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

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

            /// @brief connection between server and client
            void connect();

            /// @brief thread reception data
            void dataReception();

            /// @brief get the number of lobby in the list
            /// @return int
            int getNumberLobby();

            /// @brief add lobby at the end of the list
            /// @return void
            void addLobby(rtp::Lobby lobby);

            /// @brief remove lobby in the list depending on his position
            /// @return void
            void removeLobby(int position);


            void systemsLoop();

            // Liste des méthodes à implémenter :


        protected:
        private:
            /// @brief Setup the Registry and the multiple sparseArrays
            /// @param r The registry on which to apply this method
            void _setupRegistry(eng::Registry &reg);

            int _clientPort;
            std::list<rtp::Lobby> _listLobby;

            //For UDP
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::endpoint _client;
            boost::asio::ip::udp::socket _socket;
            boost::array<networkPayload, 1> _dataRec;
            std::vector<networkPayload> _listDataRec;

            //For TCP
            boost::asio::io_service _ioService;

            //For thread
            std::mutex _mutex;
            std::mutex _cout;
            bool _isEnd = false;

            
    };
};

#endif /* !SERVER_HPP_ */
