/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "LobbyManager.hpp"

rtp::LobbyManager::LobbyManager()
{
    
}

rtp::LobbyManager::~LobbyManager()
{
}

int rtp::LobbyManager::getNumberLobby()
{
    return (this->_listLobby.size());
}

void rtp::LobbyManager::addLobby(rtp::Lobby lobby)
{
    this->_listLobby.push_back(lobby);
}

void rtp::LobbyManager::removeLobby(int position)
{
    std::list<rtp::Lobby>::iterator it = this->_listLobby.begin();

    for (int i = 0; i <= position; i++, it++) {
        if (it != this->_listLobby.end())
            return;
    }
    this->_listLobby.erase(it);
}