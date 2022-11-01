/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(boost::asio::ip::port_type port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("0.0.0.0"), port}), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"), 3303)), _socketTCP(_ioContext), _systems(_socket, _mutex, _listDataRec, _endpoints)
{
    this->_clientPort = 0;
    _port = port;
    _isEnd = false;
    _start = false;
    _multiPlayer = true;
    _level = 1;
    //_socket.local_endpoint().port(_port);
}

rtp::Server::~Server()
{
}

void rtp::Server::dataReception()
{
    while (!_isEnd) {
        size_t len = this->_socket.receive(boost::asio::buffer(this->_dataRec));
        if (this->_dataRec[0].ACTION_NAME == LEAVE_GAME) {
            //_removeEndPoint(this->_socket.remote_endpoint().address().to_string(), this->_socket.remote_endpoint().port());
            std::cout << "Removed " << this->_dataRec[0].ACTION_NAME << "in port : " <<  this->_dataRec[0].syncId << std::endl;
        }
        std::unique_lock<std::mutex> lk(this->_mutex);
        this->_listDataRec.push_back(inputPayload_t({this->_dataRec[0].ACTION_NAME, this->_dataRec[0].syncId}));
        lk.unlock();
    }
}

void rtp::Server::afterConnection(boost::asio::ip::tcp::socket sckt)
{
    boost::array<connectPayload_t, 1> dataTbs = {OK};
    boost::system::error_code error;
    boost::array<demandConnectPayload_s, 1> dataRec;
    connectPayload_t clientIds;
    _socketList.push_back(&sckt);

    dataTbs[0].playerId = _nPlayer;
    _askNewPlayer = true;
    while (_askNewPlayer);
    dataTbs[0].syncId = _lastPlayerSyncId;
    _start = true;

    boost::asio::read(sckt, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "[Server][connect]: Receive failed: " << error.message() << std::endl;
    } else if (dataRec[0].ACTION_NAME == CONNECT) {
        std::cout << "[Server][connect]: Action receive number : " << dataRec[0].ACTION_NAME << std::endl;
        std::stringstream a;
        a << dataRec[0].addr1 << "." << dataRec[0].addr2 << "." << dataRec[0].addr3 << "." << dataRec[0].addr4;
        _addEndpoint(a.str(), dataRec[0].port);
        _multiPlayer = dataRec[0].multiplayer;
        _level = dataRec[0].level;
        std::cout << "level choose : " << _level << std::endl;
        _systems.setEnemyRate(5 - (_level / 1.9));
    } else {
        std::cout << "[Server][connect]: Wrong receive message" << dataRec[0].ACTION_NAME << std::endl;
    }
    // write operation
    sckt.send(boost::asio::buffer(dataTbs));
}

void rtp::Server::assyncConnect()
{
    _socketOptional.emplace(_ioContext);
    _acceptor.async_accept(*_socketOptional, [this] (boost::system::error_code error)
    {
        if (error) {
            std::cout << "[Server][connect]: connect failed" << std::endl;
        } else {
            std::cout << "[Server][connect]: connect success" << std::endl;
            afterConnection(std::move(*_socketOptional));
        }
        assyncConnect();
    });
}

void rtp::Server::connect()
{
    _ioContext.run();
}

void rtp::Server::run()
{
    std::string input;
    std::cout << "[Server][run]: Running..." << std::endl;
    
    
    assyncConnect();
    std::thread connect(&rtp::Server::connect, this);
    std::thread dataReception = std::thread(&rtp::Server::dataReception, this);
    std::thread systems = std::thread(&rtp::Server::systemsLoop, this);

    while (!_isEnd)
    {
        std::cin >> input;
        if (input == "help")
            _printHelp();
        if (input == "exit")
            _exitServer(systems, dataReception, connect);
        if (input == "addEnemy")
            _commandAddEnemy = true;
    }
    std::cout << "[Server]: Bye!" << std::endl;
}

void rtp::Server::_addEnemy(eng::Registry &r)
{
    eng::Entity enm = r.spawnEntity();

    r.addComponent<eng::Position>(enm, eng::Position(1920, rand() % 1080, 0));
    r.addComponent<eng::Velocity>(enm, eng::Velocity(-5, 0));
    r.addComponent<rtp::EnemyStats>(enm, rtp::EnemyStats(5 * _level, 0));
    r.addComponent<rtp::RectCollider>(enm, rtp::RectCollider(40, 16));
    r.addComponent<rtp::Synced>(enm, rtp::Synced(enm.getId()));
    _cout.lock();
    std::cout << "[Server][systemsLoop]: added an enemy!" << std::endl;
    _cout.unlock();
}

void rtp::Server::_printHelp()
{
    _cout.lock();
    std::cout << "[Server]: help\t\t display this message" << std::endl;
    std::cout << "[Server]: addEnemy\t add a random enemy" << std::endl;
    std::cout << "[Server]: exit\t\t exits the server"<< std::endl;
    _cout.unlock();
}

void rtp::Server::_exitServer(std::thread &sys, std::thread &rec, std::thread &co)
{
    // Speak to user
    _cout.lock();
    std::cout << "[Server]: Joining threads..." << std::endl;
    _cout.unlock();
    _isEnd = true;

    // Send a last msg to end data thread
    boost::array<networkPayload, 1> endmsg = {QUIT};
    _socket.send_to(boost::asio::buffer(endmsg),
    boost::asio::ip::udp::endpoint(boost::asio::ip::make_address("0.0.0.0"), _port));
    _ioContext.stop();

    // Joining threads
    sys.join();
    rec.join();
    co.join();
}

void rtp::Server::systemsLoop()
{
    //rtp::ServerSystems systems(_socket, _mutex, _listDataRec, _endpoints);
    eng::Registry r;
    _systems.setEnemyRate(5);
    _systems.setBonusRate(17);

    _setupRegistry(r);
    _cout.lock();
    std::cout << "[Server][systemsLoop]: Registry is ready" << std::endl;
    _cout.unlock();

    while (!_isEnd)
    {
        // Update delta time
        _systems.updDeltaTime();

        if (_commandAddEnemy) {
            _commandAddEnemy = false;
            _addEnemy(r);
        }
        if (_askNewPlayer) {
            _addPlayer(r);
            _askNewPlayer = false;
        }

        // Receive data
        _systems.receiveData(r);

        // Apply new controls
        _systems.controlMovementSystem(r);
        _systems.controlFireSystem(r);

        // Apply logic and physics calculations
        _systems.positionSystem(r);
        _systems.limitPlayer(r);
        _systems.playerBullets(r);
        _systems.killDeadEnemies(r);
        _systems.killOutOfBounds(r);
        _systems.spawnEnemies(r, _level);
        _systems.collisions(r);
        // systems.spawnBonus(r);

        // Send the new data
        _systems.sendData(r);

        // Limit the frequence of the server
        _systems.limitTime();
    }
    _cout.lock();
    std::cout << "[Server][systemsLoop]: Exiting systems loop" << std::endl;
    _cout.unlock();
    return;
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
    reg.registerComponents(eng::SparseArray<rtp::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<rtp::Bonus>());
}

// Player Id will be stored inside playerstats later...
void rtp::Server::_addPlayer(eng::Registry &r)
{
    eng::Entity player = r.spawnEntity();

    r.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
    r.addComponent<eng::Velocity>(player, eng::Velocity(0, 0));
    r.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(_nPlayer));
    r.addComponent<rtp::Controllable>(player, rtp::Controllable());
    r.addComponent<rtp::Synced>(player, rtp::Synced(player.getId()));
    r.addComponent<rtp::RectCollider>(player, rtp::RectCollider(40, 16));
    _lastPlayerSyncId = player.getId();
    _cout.lock();
    std::cout << "[Server][systemsLoop]: Player " << _nPlayer << "has joinded the game!" << std::endl;
    _cout.unlock();
    _nPlayer++;
}

int rtp::Server::getNumberLobby()
{
    return (this->_listLobby.size());
}

void rtp::Server::addLobby(rtp::Lobby lobby)
{
    this->_listLobby.push_back(lobby);
}

void rtp::Server::removeLobby(int position)
{
    std::list<rtp::Lobby>::iterator it = this->_listLobby.begin();

    for (int i = 0; i <= position; i++, it++)
    {
        if (it != this->_listLobby.end())
            return;
    }
    this->_listLobby.erase(it);
}

void rtp::Server::_addEndpoint(std::string address, int port)
{
    _endpoints.push_back({boost::asio::ip::make_address(address), static_cast<boost::asio::ip::port_type>(port)});
}

void rtp::Server::_removeEndPoint(std::string address, int port)
{
    auto it = _endpoints.begin();
    bool found = false;

    while (it != _endpoints.end()) {
        if (it->address() == boost::asio::ip::make_address(address)
            && it->port() == static_cast<boost::asio::ip::port_type>(port)) {
            found = true;
            break;
        }
        it++;
    }
    if (found)
        _endpoints.erase(it);
}