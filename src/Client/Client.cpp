/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(boost::asio::ip::port_type port): _port(port), _socketTCP(_ioService),
_socket(_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("0.0.0.0"), port}), _gfx(std::vector<int>({1920, 1080, 32}), "RTYPE"), _net("127.0.0.1", 3303, _socket, _gfx.getDelta())
{
    //Game game(_manager);
    //MainMenu mm(_manager);
    std::cout << "My address: <" << _socket.local_endpoint().address() << ":";
    std::cout << _socket.local_endpoint().port() << ">" << std::endl;
}

rtp::Client::~Client()
{
}

void rtp::Client::run()
{
    systemsLoop();
    //disconnect();
}

void rtp::Client::disconnect()
{
    // Disconnect here
    std::cout << "[CLIENT][DISCONNECT] : send disconnect" << std::endl;
    boost::array<inputPayload_t, 1> dataTbs = {LEAVE_GAME};
    //_socket.send_to(boost::asio::buffer(dataTbs),  boost::asio::ip::udp::endpoint{boost::asio::ip::udp::v4(), boost::asio::ip::port_type(_port)});
    boost::asio::write(_socketTCP, boost::asio::buffer(dataTbs), _error);
    return;
}

boost::array<rtp::demandConnectPayload_s, 1> rtp::Client::_fillDataToSend(std::string address)
{
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT};

    size_t pos = 0;
    std::string token;

    pos = address.find('.');
    token = address.substr(0, pos);
    dataTbs[0].addr1 = atoi(token.c_str());
    address.erase(0, pos + 1);

    pos = address.find('.');
    token = address.substr(0, pos);
    dataTbs[0].addr2 = atoi(token.c_str());
    address.erase(0, pos + 1);

    pos = address.find('.');
    token = address.substr(0, pos);
    dataTbs[0].addr3 = atoi(token.c_str());
    address.erase(0, pos + 1);

    pos = address.find('.');
    token = address.substr(0, pos);
    dataTbs[0].addr4 = atoi(token.c_str());
    
    dataTbs[0].port = _port;
    std::cout << "addresse : " << dataTbs[0].addr1 << "." << dataTbs[0].addr2 << "." << dataTbs[0].addr3 << "." << dataTbs[0].addr4 << std::endl;

    return dataTbs;
}

int rtp::Client::connect(eng::RegistryManager &manager)
{
    rtp::Game game(_manager);
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT};
    boost::array<connectPayload_t, 1> dataRec;
    std::vector<int> res;

    //ICI adress

    dataTbs[0].addr1 = 0;
    dataTbs[0].addr2 = 0;
    dataTbs[0].addr3 = 0;
    dataTbs[0].addr4 = 0;
    dataTbs[0].port = _port;

    //connection

    boost::asio::ip::tcp::resolver resolver(_ioContext);

    std::string serverName = "localhost";

    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "3303");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;

    try {

        boost::system::error_code error = boost::asio::error::host_not_found;
        _socketTCP.connect(*(resolver.resolve(query)), error);
        if (error) {
            std::cout << "[Client][Connect]: fail to connect " << error << std::endl;
        } else {
            std::cout << "[Client][Connect]: connect success" << std::endl;

        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        res.push_back(1);
        return (1);
    }

    boost::asio::write(_socketTCP, boost::asio::buffer(dataTbs), _error);

    if (_error)
        std::cout << "[Client][Connect]: send failed: " << _error.message() << std::endl;

    // getting response from server
    boost::asio::read(_socketTCP, boost::asio::buffer(dataRec), boost::asio::transfer_all(), _error);
    res.push_back(0);
    res.push_back(dataRec[0].playerId);
    res.push_back(dataRec[0].syncId);
    if (_error && _error != boost::asio::error::eof) {
        std::cout << "[Client][Connect]: receive failed: " << _error.message() << std::endl;
    } else {
        std::cout << "[Client][Connect]:action receive number : " << dataRec[0].ACTION_NAME << std::endl;
    }

    if (res[0] == 1)
        return (1);
    
    eng::Entity player = game.addPlayer(_manager.getTop(), res[1], res[2]);
    _mySyncId = res[2];
    _myPlayerId = res[1];
    _net.setSyncId(_mySyncId);

    _receiveData = std::thread(&rtp::Client::dataReception, this);
    _sendData = std::thread(&rtp::Client::dataSend, this);
    return (0);
}

void test()
{
    std::cout << "test" << std::endl;
}


void rtp::Client::dataReception()
{
    while (_gfx.windowOpen())
        _net.receiveData(_manager.getTop());
}

void rtp::Client::dataSend()
{
    while (_gfx.windowOpen())
        _net.sendData(_manager.getTop());
}

void rtp::Client::systemsLoop()
{
    rtp::ClientSystems systems(_gfx.getWindow(), _gfx.getClock(), _gfx.getDelta(), "127.0.0.1", 3303, _socket);
    std::function<int(eng::RegistryManager &)> co = std::bind(&Client::connect, this, _manager);
    rtp::MainMenu mm(_manager, co);
    eng::Registry &r = _manager.getTop();
    std::stringstream ss;
    _gfx.setMaxFrameRate(60);
    _net.writeInChatBox(r, ss.str(), rtp::NetworkSystems::ChatBoxStyle::EVENT);


    while (_gfx.windowOpen()) {
        _gfx.eventCatchWindow();
        
        // Receive Inputs
        _gfx.controlSystem(_manager.getTop());

        // Update data
        systems.controlFireSystem(_manager.getTop());
        systems.controlChatSystem(_manager.getTop());
        systems.controlMovementSystem(_manager.getTop());
        systems.shootSystem(_manager.getTop());
        systems.positionSystem(_manager.getTop());
        systems.limitPlayer(_manager.getTop());
        _gfx.animateSystem(_manager.getTop());
        _gfx.buttonStateSystem(_manager.getTop());
        systems.buttonSystem(_manager.getTop(), _manager);
        systems.playerBullets(r);
        systems.killDeadEnemies(r);
        systems.killOutOfBounds(r);
        systems.killBullets(r);

        // Display & play sounds/music
        systems.playMusicSystem(_manager.getTop());
        systems.playSoundSystem(_manager.getTop());
        _gfx.clearSystem();
        _gfx.backgroundSystem(_manager.getTop());
        _gfx.drawSystem(_manager.getTop());
        _gfx.writeSystem(_manager.getTop());
        _gfx.displaySystem();
    }
    _receiveData.join();
    _sendData.join();
    //net.disconnectSystems(r);
}