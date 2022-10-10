/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303}), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3303))
{
    this->_connect = false;
    this->_clientPort = 0;

}

rtp::Server::~Server()
{
}

bool rtp::Server::isConnected()
{
    return this->_connect;
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

void rtp::Server::run()
{

    boost::asio::io_service io_service;
    //listen for new connection
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 3304));
    //socket creation 
    boost::asio::ip::tcp::socket socket_(io_service);
    //waiting for connection
    acceptor_.accept(socket_);


        
    //read operation
    boost::array<networkPayload, 1> dataRec;
    boost::asio::read(socket_, boost::asio::buffer(dataRec), boost::asio::transfer_all());
    std::cout << dataRec[0].ACTION_NAME << std::endl;


    //write operation
    //send_(socket_, "Hello From Server!");
    boost::array<networkPayload, 1> data_tbs = {OK};
    boost::asio::write(socket_, boost::asio::buffer(data_tbs));


    std::cout << "Servent sent Hello message to Client!" << std::endl;
    
    //_acceptor.accept(_socket);
    /*for (;;) {
        std::cout << "WAITING TO RECEIVE" << std::endl;
       // boost::asio::read( this->_socket, boost::asio::buffer(this->_dataRec));
        size_t len = this->_socket.receive_from(boost::asio::buffer(this->_dataRec), this->_client);
        
        requestConnection();

        //boost::array<networkPayload, 1> data_rec;
        this->_clientPort = this->_client.port();
        std::cout << this->_client << " on port " << this->_clientPort << " sent us (" << 12 << "bytes): " << this->_dataRec[0].ACTION_NAME << " || the bodySize was " << this->_dataRec[0].bodySize << " bytes." << std::endl;
        // là dans le cas du TCP il faut réagir au ACTION_NAME reçu 
        // puis envoyer une réponde en fonction de la réaction serveur.
    }*/
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
