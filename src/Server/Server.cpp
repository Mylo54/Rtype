/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port): _udp(port), _tcp(port), _serverSystem(_udp)
{
    _isRunning = true;
    _waitingRoom = true;
    init();
}

rtp::Server::~Server()
{
}

void rtp::Server::receiveData()
{
    std::vector<int> payloadList = _udp.receive();
    while (!payloadList.empty()) {
        // Dump invalid packets
        if (payloadList.back() != 1450) {
            payloadList.pop_back();
            continue;
        }

        payloadList.pop_back();
    }
}

void rtp::Server::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<eng::Position>());
    reg.registerComponents(eng::SparseArray<eng::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
    reg.registerComponents(eng::SparseArray<eng::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<eng::RigidBody>());
    reg.registerComponents(eng::SparseArray<rtp::Canon>());
}

int rtp::Server::run()
{
    std::cout << "Server is up!" << std::endl;
    std::string input;
    _setupRegistry(_registry);

    while (_isRunning) {
        if (input == "exit")
            _isRunning = false;
        if (_waitingRoom)
            runWaitingRoom();
        else
            runGame();
        //receiveData();
    }
    return (0);
}

int rtp::Server::runWithLobby()
{
    _isRunning = true;
    std::cout << "Server is up!" << std::endl;

    std::thread serverIO(&rtp::Server::_serverIO, this);

    while (_isRunning)
        listenRequests();
    serverIO.join();
    _destroyLobbies();
    return (0);
}

void rtp::Server::init()
{
    _tcp.connect();
    _tcp.runContext();
}

void rtp::Server::listenRequests()
{
    std::vector<std::string> requests = _tcp.receive();

    for (int i = 0; i != requests.size(); i++) {
        if (requests[i] == "Create room, multiplayer")
            this->_makeLobby(true);
        if (requests[i] == "create_room, solo")
            this->_makeLobby(false);
        if (requests[i].compare(0, 11, "join_room, ") == 0)
            _joinLobby(i, atoi(requests[i].c_str()));
        if (requests[i] == "list_lobbies")
            _listLobbies(i);
    }
}

void rtp::Server::_serverIO()
{
    std::string input;

    while (_isRunning) {
        std::cin >> input;
        if (input == "exit")
            _isRunning = false;
    }
}

void rtp::Server::_joinLobby(int player, int lobbyId)
{
    
}

void rtp::Server::_makeLobby(bool isMulti)
{
    lobby_data_t *newLobby = new lobby_data_t;

    int id = _lobbies.size();
    newLobby->id = id;
    newLobby->isMulti = isMulti;
    newLobby->isRunning = true;
    newLobby->numberOfPlayers = 0;
    _lobbies.push_back(newLobby);
    _lobbyThreads.push_back(new std::thread(&rtp::Server::_lobbyRun, this, id));
}

void rtp::Server::_listLobbies(int dest)
{
    std::stringstream msg;

    for (int i = 0; i < _lobbies.size(); i++) {
        if (_lobbies[i]->isMulti) {
            msg << "lobby " << _lobbies[i]->id << ", ";
            msg << _lobbies[i]->numberOfPlayers;
            msg << "\n";
        }
    }
    std::cout << "Listing lobbies..." << std::endl;
    _tcp.sendTo(msg.str(), dest);
}

void rtp::Server::_lobbyRun(int id)
{
    auto &myData = this->_lobbies[id];
    while (myData->isRunning) {
        // do things here
    }
}

void rtp::Server::_destroyLobbies()
{
    std::cout << "Closing all lobbies..." << std::endl;
    // set all lobbies to die
    for (int i = 0; i < _lobbies.size(); i++)
        _lobbies[i]->isRunning = false;

    // join & delete all threads
    for (int i = 0; i < _lobbyThreads.size(); i++) {
        _lobbyThreads[i]->join();
        delete _lobbyThreads[i];
    }

    // destroy all data pointers
    for (int i = 0; i  < _lobbies.size(); i++)
        delete _lobbies[i];
    std::cout << "Done!" << std::endl;
}

void rtp::Server::runWaitingRoom()
{
    std::cout << "running waitingRoom" << std::endl;

    std::vector<int> res = _udp.listen();
    if (res[0] == 502) {
        _waitingRoom = false;
        std::vector<int> vec = {403};
        _udp.sendToAll(vec);
    }
    else {
        std::vector<int> vec = {404};
        _udp.sendToAll(vec);
    }

}

void rtp::Server::runGame()
{
    std::cout << "running Game" << std::endl;
    _serverSystem.receiveData(_registry);


    _serverSystem.sendData(_registry);
}