/*
** EPITECH PROJECT, 2022
** Rtype
** File description:
** TCPServer
*/

#include "TCPServer.hpp"

rtp::TCPServer::TCPServer(int port) :
_waitingSocket(_ioContext), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint{
    boost::asio::ip::tcp::v4(), static_cast<boost::asio::ip::port_type>(port)})
{
}

rtp::TCPServer::~TCPServer()
{
    if (this->_runContext.joinable())
        this->_runContext.join();
    _ioContext.stop();
}

void rtp::TCPServer::_blockFct()
{
    _ioContext.run();
}

void rtp::TCPServer::runContext()
{
    _runContext = std::thread(&rtp::TCPServer::_blockFct, this);
}

bool rtp::TCPServer::connect()
{
    _socketOptional.emplace(_ioContext);
    _acceptor.async_accept(*_socketOptional, [this] (boost::system::error_code error)
    {
        if (error) {
            std::cout << "[Server][connect]: connect failed" << std::endl;
        } else {
            std::cout << "[Server][connect]: connect success" << std::endl;

            this->_socketList.push_back(&_socketOptional.value());
            //_afterConnectionToClient(std::move(*_socketOptional));
        }
        connect();
    });
}

void rtp::TCPServer::send(std::string msg)
{
    for (auto it = _socketList.begin(); it != _socketList.end(); it++) {
        std::cout << "try send : " << msg << std::endl;
        //boost::asio::write((*it), boost::asio::buffer(data));
        (*it)->send(boost::asio::buffer(msg));
    }
}

std::string rtp::TCPServer::receiveFrom(int i)
{
    boost::system::error_code errors;
    std::string res;
    boost::array<char, 128> buf;

    if (_socketList.empty())
        return "\0";

    size_t len = _socketList[i]->receive(boost::asio::buffer(buf));

        res = buf.data();
        std::cout << res;
    /*if (!errors) {
    } else {
        std::cout << errors.message();
    }*/
    return res;
}


std::vector<std::string> rtp::TCPServer::receive()
{
    boost::system::error_code errors;
    std::vector<std::string> res;

    for (int i = 0; i < _socketList.size(); i++) {
        boost::array<char, 128> buf;
        size_t len = _socketList[i]->read_some(boost::asio::buffer(buf), errors);
        if (!errors) {
            std::string r = buf.data();
            std::cout << r;
            res.push_back(r);
        }

    }
    return res;
}
