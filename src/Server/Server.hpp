/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include "../Network/UDPServer.hpp"
#include "../Network/TCPServer.hpp"

namespace rtp
{
    typedef struct lobby_data_s {
        int id;
        bool isMulti;
        int numberOfPlayers;
        bool isRunning;
    } lobby_data_t;

    class Server {
        public:
            Server(int port);
            ~Server();

            void init();
            int run();

            void listenRequests();
        protected:
        private:
            void _serverIO();
            void _makeLobby(bool isMulti);
            void _joinLobby(int player, int lobbyId);
            void _listLobbies(int dest);
            void _lobbyRun(int id);
            void _destroyLobbies();

            bool _isRunning = false;
            rtp::UDPServer _udp;
            rtp::TCPServer _tcp;
            std::vector<lobby_data_t *> _lobbies;
            std::vector<std::thread *> _lobbyThreads;
    };
} // namespace rtp

#endif /* !SERVER_HPP_ */
