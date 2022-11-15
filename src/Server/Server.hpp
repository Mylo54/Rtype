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
#include "../System/EnemySystem.hpp"

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
            void addPlayers();
            eng::Entity addPlayer(eng::Registry &reg, int playerId, int syncId);
            void receiveDataLoop();
        protected:
        private:
            void _serverIO();
            void _makeLobby(bool isMulti);
            void _joinLobby(int player, int lobbyId);
            void _listLobbies(int dest);
            void _lobbyRun(int id);
            void _destroyLobbies();
            void _setupRegistry(eng::Registry &reg);

            /// @brief The time to wait between each enemy spawn
            float _enemyRate;
            /// @brief The timer until the next enemy spawns
            float _enemyTimer;
            int _level;
            bool _isRunning = false;
            rtp::UDPServer _udp;
            rtp::TCPServer _tcp;
            std::vector<lobby_data_t *> _lobbies;
            std::vector<std::thread *> _lobbyThreads;
            rtp::ServerSystem _serverSystem;
            rtp::PlayerSystem _playerSystem;
            eng::PhysicSystems _physicSystem;
            rtp::KillSystem _killSystem;
            rtp::EnemySystem _enemySystem;
            eng::TextureManager _textureManager;
            eng::Registry _registry;
            std::vector<int> _inputList;
            std::mutex _dataMutex;
            bool _waitingRoom;
            int _score = 0;
            int _lastSyncId = 0;
    };
} // namespace rtp

#endif /* !SERVER_HPP_ */
