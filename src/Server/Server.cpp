/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(boost::asio::ip::port_type port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), port})
{
    this->_clientPort = 0;
    _port = port;
    //_socket.local_endpoint().port(_port);
}

rtp::Server::~Server()
{
}
/*
void rtp::Server::requestConnection()
{
    if (this->_dataRec[0].ACTION_NAME == ACTIONTYPE_PREGAME::CONNECT) {
        std::cout << "client ask for connection" << std::endl;
        addLobby(Lobby());
        //TODO: create thread for client
        boost::array<networkPayload, 1> data = {OK};
        //boost::asio::write(this->_socket, boost::asio::buffer(data));
        this->_socket.send_to(boost::asio::buffer(data), this->_client);
    }
}*/

void rtp::Server::connect()
{
    boost::system::error_code error;
    boost::array<networkPayload, 1> dataRec;
    boost::asio::ip::tcp::acceptor::endpoint_type endType;
    // listen for new connection
    boost::asio::ip::tcp::acceptor acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3303));
    // socket creation
    boost::asio::ip::tcp::socket socket(_ioService);
    // waiting for connection
    acceptor.accept(socket, endType);

    // read operation
    boost::asio::read(socket, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << std::endl;
    } else if (dataRec[0].ACTION_NAME == CONNECT) {
        std::cout << "action receive number : " << dataRec[0].ACTION_NAME << std::endl;
        std::string sClientIp = endType.address().to_string();
    } else {
        std::cout << "wrong receive message" << dataRec[0].ACTION_NAME << std::endl;
    }

    // write operation
    boost::array<networkPayload, 1> dataTbs = {OK};
    boost::asio::write(socket, boost::asio::buffer(dataTbs));

    std::cout << "Server connected to Client!" << std::endl;
}

void rtp::Server::dataReception()
{
    while (!_isEnd)
    {
        _cout.lock();
        std::cout << "[Server][dataReception]: Waiting to receive" << std::endl;
        _cout.unlock();
        size_t len = this->_socket.receive(boost::asio::buffer(this->_dataRec));

        _cout.lock();
        std::cout << "[Server][dataReception]: Received something!" << std::endl;
        _cout.unlock();

        std::unique_lock<std::mutex> lk(this->_mutex);
        this->_listDataRec.push_back(networkPayload({this->_dataRec[0].ACTION_NAME, this->_dataRec[0].bodySize, this->_dataRec[0].body}));
        lk.unlock();
        _cout.lock();
        std::cout << "[Server][dataReception]: "
                  << "A client"
                  << " on port " << this->_clientPort << " sent us (" << 12 << "bytes): " << this->_dataRec[0].ACTION_NAME << " || the bodySize was " << this->_dataRec[0].bodySize << " bytes." << std::endl;
        _cout.unlock();
    }
    _cout.lock();
    std::cout << "[Server][dataReception]: Exiting data reception loop" << std::endl;
    _cout.unlock();
}

void rtp::Server::run()
{
    std::string input;
    std::cout << "[Server][dataReception]: Running..." << std::endl;
    connect();

    std::thread dataReception(&rtp::Server::dataReception, this);
    std::thread systems(&rtp::Server::systemsLoop, this);

    while (!_isEnd)
    {
        std::cin >> input;
        if (input == "help")
            _printHelp();
        if (input == "exit")
            _exitServer(systems, dataReception);
    }
    std::cout << "[Server]: Bye!" << std::endl;
}

void rtp::Server::_printHelp()
{
    _cout.lock();
    std::cout << "[Server]: exit\t exits the server"<< std::endl;
    _cout.unlock();
}

void rtp::Server::_exitServer(std::thread &sys, std::thread &rec)
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
    
    // Joining threads
    sys.join();
    rec.join();
}

void rtp::Server::systemsLoop()
{
    rtp::ServerSystems systems(this->_socket, this->_mutex, this->_listDataRec);
    eng::Registry r;

    _setupRegistry(r);

    _cout.lock();
    std::cout << "[Server][systemsLoop]: Registry is ready" << std::endl;
    _cout.unlock();

    while (!_isEnd)
    {
        // Receive data
        systems.receiveData(r);

        // Apply new controls
        systems.controlSystem(r);
        systems.controlMovementSystem(r);
        systems.controlFireSystem(r);

        // Apply logic and physics calculations
        systems.positionSystem(r);

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
