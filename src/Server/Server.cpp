/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port) : _socket(this->_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303})
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
        //createLobby
    }
}

void rtp::Server::run()
{
    for (;;) {
        std::cout << "WAITING TO RECEIVE\n";
        size_t len = this->_socket.receive_from(boost::asio::buffer(this->_dataRec), this->_client);
        
        requestConnection();

        //boost::array<networkPayload, 1> data_rec;
        this->_clientPort = this->_client.port();
        std::cout << this->_client << " on port " << this->_clientPort << " sent us (" << len << "bytes): " << this->_dataRec[0].ACTION_NAME << " || the bodySize was " << this->_dataRec[0].bodySize << " bytes." << std::endl;
        // là dans le cas du TCP il faut réagir au ACTION_NAME reçu 
        // puis envoyer une réponde en fonction de la réaction serveur.
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
