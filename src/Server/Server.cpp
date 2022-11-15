/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port): _udp(port), _tcp(port), _serverSystem(_udp), _physicSystem(_serverSystem.getDelta())
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
    reg.registerComponents(eng::SparseArray<eng::Drawable>());
}

void rtp::Server::receiveDataLoop()
{
    while (_isRunning) {
        if (_waitingRoom)
            continue;
        std::vector<int> data = _udp.receive();
        _dataMutex.lock();
        for (int i = 0; i < data.size(); i++)
            _inputList.push_back(data[i]);
        _dataMutex.unlock();
    }
}

int rtp::Server::run()
{
    std::cout << "Server is up!" << std::endl;
    std::string input;
    std::thread receiveDataThread(&rtp::Server::receiveDataLoop, this);
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
    receiveDataThread.join();
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
    std::vector<int> res = _udp.listen();
    if (res[0] == 502) {
        _waitingRoom = false;
        addPlayers();
    }
    else {
        std::vector<int> vec = {404, _udp.getNumberOfClients()};
        _udp.sendToAll(vec);
    }
}

void rtp::Server::runGame()
{
    _serverSystem.receiveData(_registry, _inputList, _dataMutex);

    _playerSystem.controlMovement(_registry, _serverSystem.getDelta());
    _physicSystem.applyGravity(_registry);

    _physicSystem.applyVelocities(_registry);
    _playerSystem.limitPlayer(_registry);
    // Shooting
    _playerSystem.controlFireSystem(_registry, _serverSystem.getDelta());
    _playerSystem.shootSystem(_registry);
    // Kill
    _killSystem.killOutOfBounds(_registry);
    _killSystem.killBullets(_registry);
    _killSystem.killDeadEnemiesServer(_registry);
    _killSystem.killDeadPlayers(_registry);
    // Victory / defeat
    _waitingRoom = _killSystem.allPlayerKilled(_registry) || (_level == 5 && _score >= 10000) || (_level >= 1 && _level <= 4 && _score >= _level * 100);

    // Enemy
    _enemySystem.playerBullets(_registry);
    _enemySystem.enemyCollision(_registry, _physicSystem);
    if (_level == 5)
        _enemySystem.bossAnimation(_registry);
    _enemySystem.spawnEnemies(_registry, _enemyTimer, _level, _serverSystem.getDelta(), _textureManager);

    _serverSystem.sendData(_registry);
}

void rtp::Server::addPlayers()
{
    std::vector<int> vec = {403};
    for (int i = 0; i < _udp.getNumberOfClients(); i++) {
        _lastSyncId += 1;
        addPlayer(_registry, i + 1, _lastSyncId);
        vec.push_back(i + 1);
        vec.push_back(_lastSyncId);
    }
    _udp.sendToAll(vec);
    _udp.sendToAll(vec);
    _udp.sendToAll(vec);
    _udp.sendToAll(vec);
}

eng::Entity rtp::Server::addPlayer(eng::Registry &reg, int playerId, int syncId)
{
    eng::Entity player = reg.spawnEntity();
    std::stringstream name;
    name << "P" << playerId;

    reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    reg.addComponent<eng::Velocity>(player, eng::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 500, 4, {50, 15}));
    reg.addComponent<rtp::Canon>(player, rtp::Canon("assets/missile.png", 300, 0.1, {10, -20}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    reg.addComponent<eng::RectCollider>(player, eng::RectCollider(40, 16));
    reg.addComponent<eng::RigidBody>(player, eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));
    reg.addComponent<eng::Writable>(player, eng::Writable("Player name", name.str(), "assets/MetroidPrimeHunters.ttf", 30, sf::Color::Yellow, sf::Text::Regular, 20, -35));

    return player;
}