/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server
*/

#include "LobbyManager.hpp"

rt::LobbyManager::LobbyManager()
{
    
}

rt::LobbyManager::~LobbyManager()
{
}

int rt::LobbyManager::getNumberLobby()
{
    return (this->_listLobby.size());
}

void rt::LobbyManager::addLobby(rt::Lobby lobby)
{
    this->_listLobby.push_back(lobby);
}

void rt::LobbyManager::removeLobby(int position)
{
    std::list<rt::Lobby>::iterator it = this->_listLobby.begin();

    for (int i = 0; i <= position; i++, it++) {
        if (it != this->_listLobby.end())
            return;
    }
    this->_listLobby.erase(it);
}