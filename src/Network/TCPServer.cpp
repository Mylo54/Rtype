/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** TCPServer
*/

#include "TCPServer.hpp"
#include <iostream>

rtp::TCPServer::TCPServer(int port) :
_waitingSocket(_ioContext), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint{
    boost::asio::ip::tcp::v4(), static_cast<boost::asio::ip::port_type>(port)})
{
}

rtp::TCPServer::~TCPServer()
{
    _ioContext.stop();
    if (this->_runContext.joinable())
        this->_runContext.join();
}

void rtp::TCPServer::_blockFct()
{
    _ioContext.run();
}

void rtp::TCPServer::runContext()
{
    _runContext = std::thread(&rtp::TCPServer::_blockFct, this);
}

void rtp::TCPServer::connect()
{
    _socketOptional.emplace(_ioContext);
    _acceptor.async_accept(*_socketOptional, [this] (boost::system::error_code error)
    {
        if (error) {
            std::cout << "[Server][connect]: connect failed" << std::endl;
        } else {
            std::cout << "[Server][connect]: connect success" << std::endl;

            // we must build a new object on the stack, not push a reference
            // to a heap object that will be destroyed later...
            // maybe std::move will do the trick, else use some news and deletes
            this->_socketList.push_back(&_socketOptional.value());
            //_afterConnectionToClient(std::move(*_socketOptional));
        }
        connect();
    });
}

static std::string makePayload(std::string msg)
{
    std::stringstream res;

    res << msg.length() << ":" << msg;
    return (res.str());
}

void rtp::TCPServer::sendTo(std::string msg, int dest)
{
    _socketList[dest]->send(boost::asio::buffer(makePayload(msg)));
}

void rtp::TCPServer::send(std::string msg)
{
    for (auto it = _socketList.begin(); it != _socketList.end(); it++) {
        (*it)->send(boost::asio::buffer(makePayload(msg)));
    }
}

std::string rtp::TCPServer::receiveFrom(int i)
{
    std::string res;
    std::array<char, 1> numBuf;
    std::vector<char> buf;

    if (_socketList.empty())
        return res;
    // get msg size
    while (true) {
        boost::asio::read(*_socketList[i], boost::asio::buffer(numBuf));
        if (numBuf[0] == ':')   // end of size header
            break;
        res.append(1, numBuf[0]);
    }
    buf.resize(atoi(res.c_str()));

    // get msg
    boost::asio::read(*_socketList[i], boost::asio::buffer(buf));
    res.clear();
    res.append(buf.data());
    return (res);
}


std::vector<std::string> rtp::TCPServer::receive()
{
    std::vector<std::string> res;
    std::string sizeHeader;
    std::array<char, 1> numBuf;
    std::vector<char> buffer;

    if (_socketList.empty())
        return (res);

    std::cout << "receiving..." << std::endl;
    for (int i = 0; i < _socketList.size(); i++) {
        while (true) {
            // crash here, see line 43 for more infos
            boost::asio::read(*_socketList[i], boost::asio::buffer(numBuf));
            if (numBuf[0] == ':')   // end of size header
                break;
            sizeHeader.append(1, numBuf[0]);
        }
        buffer.resize(atoi(sizeHeader.c_str()));
        boost::asio::read(*_socketList[i], boost::asio::buffer(buffer));
        res.push_back(buffer.data());
        buffer.clear();
    }
    return (res);
}
