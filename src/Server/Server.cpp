/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303})
{
    this->_clientPort = 0;
}

rtp::Server::~Server()
{
}

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
}

void rtp::Server::connect()
{
    //listen for new connection
    boost::asio::ip::tcp::acceptor acceptor(_ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3304));
    //socket creation 
    boost::asio::ip::tcp::socket socket(_ioService);
    //waiting for connection
    acceptor.accept(socket);
        
    //read operation
    boost::array<networkPayload, 1> dataRec;
    boost::asio::read(socket, boost::asio::buffer(dataRec), boost::asio::transfer_all());
    std::cout << dataRec[0].ACTION_NAME << std::endl;

    //write operation
    boost::array<networkPayload, 1> dataTbs = {OK};
    boost::asio::write(socket, boost::asio::buffer(dataTbs));

    std::cout << "Servent sent Hello message to Client!" << std::endl;
}

void rtp::Server::dataReception()
{
    std::cout << "WAITING TO RECEIVE" << std::endl;
    size_t len = this->_socket.receive_from(boost::asio::buffer(this->_dataRec), this->_client);

    this->_clientPort = this->_client.port();
    std::unique_lock<std::mutex> lk(this->_mutex);
    this->_listDataRec.push_back(networkPayload({this->_dataRec[0].ACTION_NAME, this->_dataRec[0].bodySize, this->_dataRec[0].body}));
    lk.unlock();
    std::cout << this->_client << " on port " << this->_clientPort << " sent us (" << 12 << "bytes): " << this->_dataRec[0].ACTION_NAME << " || the bodySize was " << this->_dataRec[0].bodySize << " bytes." << std::endl;
}

void rtp::Server::run()
{
    connect();

    /*creer les deux theads :
        -engine et system loop
        -data reception
    */
    // std::thread(&rtp::Server::systemsLoop, this);

    for (;;) {
        std::cout << "WAITING TO RECEIVE" << std::endl;
        size_t len = this->_socket.receive_from(boost::asio::buffer(this->_dataRec), this->_client);

        this->_clientPort = this->_client.port();
        std::cout << this->_client << " on port " << this->_clientPort << " sent us (" << 12 << "bytes): " << this->_dataRec[0].ACTION_NAME << " || the bodySize was " << this->_dataRec[0].bodySize << " bytes." << std::endl;
    }
}

void rtp::Server::systemsLoop()
{
    rtp::ServerSystems systems("127.0.0.1", 3304, this->_socket);
    eng::Registry r;

    while (true) {
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

    for (int i = 0; i <= position; i++, it++) {
        if (it != this->_listLobby.end())
            return;
    }
    this->_listLobby.erase(it);
}
