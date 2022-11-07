/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Network
*/

#include "Network.hpp"

rtp::Network::Network()
{
}

rtp::Network::~Network()
{
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
    _mySyncId = dataRec[0].syncIdc;
    return (0);
}

int rtp::Network::connectionToServer(bool multiplayer, int lvl, int port)
{
    boost::system::error_code error;
    boost::asio::ip::tcp::resolver resolver(_ioContext);
    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "3303");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;
    _port = port;

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