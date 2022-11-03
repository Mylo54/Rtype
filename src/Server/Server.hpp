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
#include <ctime>

#include "Lobby.hpp"
#include "../Components/Components.hpp"
#include "../ServerSystems/ServerSystems.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>

namespace rtp {
    /// @brief A class holding a server
    class Server {
        public:
            /// @brief Server object constructor
            /// @param port port of the server
            Server(boost::asio::ip::port_type port);
            ~Server();
            /// @brief run the server
            void run();
            //void requestConnection();

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

            /// @brief thread fonction for the loop whith all systems
            /// @return void
            void systemsLoop();

            /// @brief fonction for client to connect to the server
            /// @return void
            void assyncConnect();

        protected:
        private:
            /// @brief Adds a player into a registry, setting up everything
            /// @param r The registry on which to add a player
            void _addPlayer(eng::Registry &r);

            /// @brief Adds an endpoint into the vector of endpoints
            /// @param address The adress of the endpoint
            /// @param port The port of the endpoint
            void _addEndpoint(std::string address, int port);

            /// @brief Remove an endpoint from the vector of endpoints
            /// @param address The adress of the endpoint
            /// @param port The port of the endpoint
            void _removeEndPoint(std::string address, int port);

            /// @brief Setup the Registry and the multiple sparseArrays
            /// @param r The registry on which to apply this method
            void _setupRegistry(eng::Registry &reg);

            /// @brief Exit and join everything on the server
            /// @param sys The system loop thread
            /// @param rec The reception loop thread
            void _exitServer(std::thread &sys, std::thread &rec, std::thread &co);

            /// @brief Print a list of commands for the user
            void _printHelp();

            /// @brief Adds a random enemy into the registry
            void _addEnemy(eng::Registry &r);

            /// @brief Execute when connection is established : confirm client connection
            /// @param sckt : client socket
            void afterConnection(boost::asio::ip::tcp::socket sckt);

            boost::asio::ip::port_type _port;
            int _clientPort;
            std::list<rtp::Lobby> _listLobby;
            bool _commandAddEnemy = false;
            bool _askNewPlayer = false;
            int _nPlayer = 1;
            int _lastPlayerSyncId = 0;

            // For UDP
            boost::asio::io_context _ioContext;
            boost::asio::ip::udp::socket _socket;
            boost::array<inputPayload_t, 1> _dataRec;
            std::vector<std::vector<int>> _listDataRec;
            std::vector<boost::asio::ip::udp::endpoint> _endpoints;

            // For TCP
            boost::asio::io_service _ioService;
            boost::asio::ip::tcp::acceptor _acceptor;
            boost::asio::ip::tcp::socket _socketTCP;
            std::optional<boost::asio::ip::tcp::socket> _socketOptional;
            std::vector<boost::asio::ip::tcp::socket *> _socketList;

            // For thread
            std::mutex _mutex;
            std::mutex _cout;
            std::mutex _commands;
            bool _isEnd;
            bool _start;

            // Clock
            std::clock_t _clock;
    };
};

#endif /* !SERVER_HPP_ */
