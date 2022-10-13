/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(boost::asio::ip::port_type port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), port}), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3303)), _socketTCP(_ioContext)
{
    this->_clientPort = 0;
    _port = port;
    _isEnd = false;
    _start = false;
    //_socket.local_endpoint().port(_port);
}

rtp::Server::~Server()
{
}

void rtp::Server::dataReception()
{
    while (!_isEnd) {
        _cout.lock();
        std::cout << "[Server][dataReception]: Waiting to receive" << std::endl;
        _cout.unlock();
        size_t len = this->_socket.receive(boost::asio::buffer(this->_dataRec));

        _cout.lock();
        std::cout << "[Server][dataReception]: Received something!" << std::endl;
        _cout.unlock();

        std::unique_lock<std::mutex> lk(this->_mutex);
        this->_listDataRec.push_back(inputPayload_t({this->_dataRec[0].ACTION_NAME, this->_dataRec[0].syncId}));
        lk.unlock();
        _cout.lock();
        std::cout << "A client sent us the action type: <" << _dataRec[0].ACTION_NAME;
        std::cout << "> for the synced component <" << _dataRec[0].syncId << std::endl;
        _cout.unlock();
    }
    _cout.lock();
    std::cout << "[Server][dataReception]: Exiting data reception loop" << std::endl;
    _cout.unlock();
}

void rtp::Server::aferConnection(boost::asio::ip::tcp::socket sckt)
{
    boost::array<connectPayload_t, 1> dataTbs = {OK};
    boost::system::error_code error;
    boost::array<demandConnectPayload_s, 1> dataRec;
    connectPayload_t clientIds;

    dataTbs[0].playerId = 1;
    dataTbs[0].syncId = 1;
    _start = true;
             
    boost::asio::read(sckt, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "[Server][connect]: Receive failed: " << error.message() << std::endl;
    } else if (dataRec[0].ACTION_NAME == CONNECT) {
        std::cout << "[Server][connect]: Action receive number : " << dataRec[0].ACTION_NAME << std::endl;
        std::stringstream a;
        a << dataRec[0].addr1 << "." << dataRec[0].addr2 << "." << dataRec[0].addr3 << "." << dataRec[0].addr4;
        _addEndpoint(a.str(), dataRec[0].port);
    } else {
        std::cout << "[Server][connect]: Wrong receive message" << dataRec[0].ACTION_NAME << std::endl;
    }
    // write operation
    sckt.send(boost::asio::buffer(dataTbs));
}

void rtp::Server::assyncConnect()
{
    //Non bloquant
    _socketOptional.emplace(_ioContext);
    _acceptor.async_accept(*_socketOptional, [this] (boost::system::error_code error)
    {
        std::cout << "[Server][connect]: start accept" << std::endl;
        if (error) {
            std::cout << "[Server][connect]: connect failed" << std::endl;
            // Failed to accept
        } else {
            std::cout << "[Server][connect]: connect success" << std::endl;
            aferConnection(std::move(*_socketOptional));
        }
        assyncConnect();
    });
}

void rtp::Server::connect()
{
    _ioContext.run();
    std::cout << "[Server][connect]: after run" << std::endl;
    _cout.lock();
    std::cout << "[Server][connect]: End loop" << std::endl;
    _cout.unlock();
}


void rtp::Server::run()
{
    std::string input;
    std::cout << "[Server][RUN]: Running..." << std::endl;
    
    
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
    }
    std::cout << "[Server]: Bye!" << std::endl;
}

void rtp::Server::_printHelp()
{
    _cout.lock();
    std::cout << "[Server]: exit\t exits the server"<< std::endl;
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
    boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), _port));
    _ioContext.stop();
    
    //_socketTCP.send(boost::asio::buffer(boost::array<networkPayload, 1> {QUIT}));
    //boost::asio::write(_socketTCP, boost::asio::buffer(boost::array<networkPayload, 1> {QUIT})/*, _acceptor.local_endpoint()*/);
    
    // Joining threads
    sys.join();
    rec.join();
    co.join();
}

void rtp::Server::systemsLoop()
{
    rtp::ServerSystems systems(_socket, _mutex, _listDataRec, _endpoints);
    eng::Registry r;

    _setupRegistry(r);
    // Temporary way to add player
    _addPlayer(r, 1, 1);

    _cout.lock();
    std::cout << "[Server][systemsLoop]: Registry is ready" << std::endl;
    _cout.unlock();

    while (!_isEnd)
    {
        // Receive data
        systems.receiveData(r);

        // Update delta time
        systems.updDeltaTime();

        // Apply new controls
        systems.controlMovementSystem(r);
        systems.controlFireSystem(r);

        // Apply logic and physics calculations
        systems.positionSystem(r);
        //systems.playerLogSystem(r);

        // Send the new data
        systems.sendData(r);
    }
    _cout.lock();
    std::cout << "[Server][systemsLoop]: Exiting systems loop" << std::endl;
    _cout.unlock();
    return;
}

void rtp::Server::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
}

// Player Id will be stored inside playerstats later...
void rtp::Server::_addPlayer(eng::Registry &r, int syncId, int playerId)
{
    eng::Entity player = r.spawnEntity();

    r.addComponent<rtp::Position>(player, rtp::Position(200, 540, 0));
    r.addComponent<rtp::Velocity>(player, rtp::Velocity(0, 0));
    r.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
    r.addComponent<rtp::Controllable>(player, rtp::Controllable());
    r.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    _cout.lock();
    std::cout << "[Server][systemsLoop]: Player " << syncId << " has joined the registry" << std::endl;
    _cout.unlock();
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