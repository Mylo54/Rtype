/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../GameComponent/Controllable.hpp"
#include "../GameComponent/PlayerStats.hpp"
#include "../GameComponent/Shooter.hpp"
#include "../GameComponent/Canon.hpp"
#include "../GameComponent/Bullet.hpp"
#include "../GameComponent/Synced.hpp"
#include "../GameComponent/EnemyStats.hpp"
#include "../Network/TCPServer.hpp"
#include "../System/ServerSystem.hpp"
#include "../System/PlayerSystem.hpp"
#include "../System/KillSystem.hpp"

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
            int runWithLobby();

            void listenRequests();
            void receiveData();
            void runWaitingRoom();
            void runGame();
        protected:
        private:
            void _serverIO();
            void _makeLobby(bool isMulti);
            void _joinLobby(int player, int lobbyId);
            void _listLobbies(int dest);
            void _lobbyRun(int id);
            void _destroyLobbies();
            void _setupRegistry(eng::Registry &reg);

            bool _isRunning = false;
            rtp::UDPServer _udp;
            rtp::TCPServer _tcp;
            std::vector<lobby_data_t *> _lobbies;
            std::vector<std::thread *> _lobbyThreads;
            rtp::ServerSystem _serverSystem;
            rtp::PlayerSystem _playerSystem;
            eng::PhysicSystems _physicSystem;
            rtp::KillSystem _killSystem;
            eng::Registry _registry;
            bool _waitingRoom;
            int _score = 0;
    };
} // namespace rtp

#endif /* !SERVER_HPP_ */
