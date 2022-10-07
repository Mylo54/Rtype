/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "Server.hpp"

rtp::Server::Server(int port)
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

void rtp::Server::run()
{
    boost::asio::io_context io_context;

    for (;;) {
        boost::asio::ip::udp::socket socket(io_context, boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), 3303});
        boost::asio::ip::udp::endpoint client;

        std::cout << "WAITING TO RECEIVE\n";
        boost::array<networkPayload, 1> data_rec;

        size_t len = socket.receive_from(boost::asio::buffer(data_rec), client);
        this->_clientPort = client.port();
        std::cout << client << " on port " << this->_clientPort << " sent us (" << len << "bytes): " << data_rec[0].ACTION_NAME << " || the bodySize was " << data_rec[0].bodySize << " bytes." << std::endl;
    
    
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
