/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Network
*/

#include "Network.hpp"

rtp::Network::Network(int port):
_socketUDP(_ioContext, boost::asio::ip::udp::endpoint{
    boost::asio::ip::udp::v4(),static_cast<boost::asio::ip::port_type>(port)}),
_waitingSocket(_ioContext), _acceptor(_ioContext, boost::asio::ip::tcp::endpoint{
    boost::asio::ip::tcp::v4(), static_cast<boost::asio::ip::port_type>(port)})
{
}

rtp::Network::~Network()
{
}

void rtp::Network::UDPaddEndpoint(std::string address, int port)
{
    _UDPendpoints.push_back({
        boost::asio::ip::make_address(address),
        static_cast<boost::asio::ip::port_type>(port)
    });
}

void rtp::Network::UDPremoveEndpoint(int id)
{
    
}

void rtp::Network::UDPremoveEndpoint(std::string address, int port)
{

}

void rtp::Network::UDPsendData(std::vector<int> &data)
{
    for (int i = 0; i < _UDPendpoints.size(); i++)
        _socketUDP.send_to(boost::asio::buffer(data), _UDPendpoints[i]);
}

void rtp::Network::UDPsendDataTo(std::vector<int> &data, int to)
{
    _socketUDP.send_to(boost::asio::buffer(data), _UDPendpoints[to]);
}

std::vector<int> rtp::Network::UDPreceiveData()
{
    std::vector<int> res;

    _socketUDP.wait(boost::asio::socket_base::wait_type::wait_read);
    res.resize(_socketUDP.available() / 4);
    _socketUDP.receive(boost::asio::buffer(res));
    return (res);
}

int rtp::Network::_sendAfterConnectToServer(bool multiplayer, int lvl, int port)
{
    boost::system::error_code error;
    boost::array<connectPayload_t, 1> dataRec;
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT, 0, 0, 0, 0, port, multiplayer, lvl};


    boost::asio::write(_socketTCP, boost::asio::buffer(dataTbs), error);

    if (error)
        std::cout << "[Client][Connect]: send failed: " << error.message() << std::endl;

    // getting response from server
    boost::asio::read(_socketTCP, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);

    if (error && error != boost::asio::error::eof) {
        std::cout << "[Client][Connect]: receive failed: " << error.message() << std::endl;
        return (1);
    } else {
        std::cout << "[Client][Connect]:action receive number : " << dataRec[0].ACTION_NAME << std::endl;
    }
    _myPlayerId = dataRec[0].playerId;
    _mySyncId = dataRec[0].syncId;
    return (0);
}

int rtp::Network::connectionToServer(bool multiplayer, int lvl, int port)
{
    boost::system::error_code error;
    boost::asio::ip::tcp::resolver resolver(_ioContext);
    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "3303");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;

    try {

        boost::system::error_code error = boost::asio::error::host_not_found;
        _socketTCP.connect(*(resolver.resolve(query)), error);
        if (error) {
            std::cout << "[Client][Connect]: fail to connect " << error << std::endl;
            return (1);
        } else {
            std::cout << "[Client][Connect]: connect success" << std::endl;

        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (_sendAfterConnectToServer(multiplayer, lvl, port));
}

boost::array<rtp::demandConnectPayload_s, 1> rtp::Network::_afterConnectionToClient(boost::asio::ip::tcp::socket sckt)
{
    boost::array<connectPayload_t, 1> dataTbs = {OK};
    boost::system::error_code error;
    boost::array<demandConnectPayload_s, 1> dataRec;
    connectPayload_t clientIds;
    _socketList.push_back(&sckt);

    /*dataTbs[0].playerId = _nPlayer;
    _askNewPlayer = true;
    while (_askNewPlayer);
    dataTbs[0].syncId = _lastPlayerSyncId;
    _start = true;*/

    dataTbs[0].playerId = 0;
    dataTbs[0].syncId = 1;

    boost::asio::read(sckt, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "[Server][connect]: Receive failed: " << error.message() << std::endl;
    } else if (dataRec[0].ACTION_NAME == CONNECT) {
        std::cout << "[Server][connect]: Action receive number : " << dataRec[0].ACTION_NAME << std::endl;
        std::stringstream a;
        a << dataRec[0].addr1 << "." << dataRec[0].addr2 << "." << dataRec[0].addr3 << "." << dataRec[0].addr4;
        UDPaddEndpoint(a.str(), dataRec[0].port);
    } else {
        std::cout << "[Server][connect]: Wrong receive message" << dataRec[0].ACTION_NAME << std::endl;
    }
    // write operation
    sckt.send(boost::asio::buffer(dataTbs));
    return dataRec;
}

void rtp::Network::connectToClient()
{
    std::cout << "[Server][connect]: debug connect async" << std::endl;

    /*boost::asio::ip::tcp::acceptor acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"), 3303));
    _socketOptional.emplace(_ioContext);
    _acceptor.async_accept(*_socketOptional, [this] (boost::system::error_code error)
    {
        if (error) {
            std::cout << "[Server][connect]: connect failed" << std::endl;
        } else {
            std::cout << "[Server][connect]: connect success" << std::endl;
            _afterConnectionToClient(std::move(*_socketOptional));
        }
        connectToClient();
    });*/
}

bool rtp::Network::connect(std::string host, std::string service)
{
    boost::asio::ip::tcp::resolver resolver(_ioContext);
    boost::asio::ip::tcp::resolver::results_type endpoints =
        resolver.resolve(host, service);
    boost::system::error_code error;

    boost::asio::connect(_socketTCP, endpoints, error);
    if (error)
        return false;
    return true;
}

void rtp::Network::listen()
{
    _acceptor.async_accept(this->_waitingSocket, [this] (boost::system::error_code error) {
        if (!error)
            this->_socketList.push_back(&_waitingSocket);
    });
}

void rtp::Network::TCPsendData(std::string data)
{
    for (auto it = _socketList.begin(); it != _socketList.end(); it++)
        (*it)->send(boost::asio::buffer(data));
}

void rtp::Network::TCPsendDataTo(std::string data, int to)
{
    _socketList[to]->send(boost::asio::buffer(data));
}

std::string rtp::Network::TCPreceiveDataFrom(int from)
{
    std::string res;

    // get the string in _socketList[from].receive
    // put it in res

    return (res);
}