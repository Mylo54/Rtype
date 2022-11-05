/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(boost::asio::ip::port_type port): _port(port), _socketTCP(_ioService),
_socket(_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("0.0.0.0"), port}),
_gfx(1920, 1080, "CHLOEMIAMIAMRTYPE"),
_net("127.0.0.1", 3303, _socket, _gfx.getDelta(), _textureManager),
_inputs(_gfx.getRenderWindow())
{
    //Game game(_manager);
    //MainMenu mm(_manager);
    std::cout << "My address: <" << _socket.local_endpoint().address() << ":";
    std::cout << _socket.local_endpoint().port() << ">" << std::endl;
}

rtp::Client::~Client()
{
}

void rtp::Client::_setupInputs()
{
    _inputs.addAction("MouseLeft");
    _inputs.addAction("Move x");
    _inputs.addAction("Move y");
    _inputs.addAction("Fire");
    _inputs.addAction("Pause");
    //Thoses are for digital (button) mouvement
    _inputs.addAction("Move -x");
    _inputs.addAction("Move -y");

    // Controller inputs
    _inputs.addEvent("Move x", eng::SuperInput::JoyAnalog::leftStickX, 0);
    _inputs.addEvent("Move y", eng::SuperInput::JoyAnalog::leftStickY, 0);
    _inputs.addEvent("Fire", eng::SuperInput::JoyAnalog::rightTrigger, 0);
    _inputs.addEvent("Fire", eng::SuperInput::JoyButton::a, 0);
    _inputs.addEvent("Fire", eng::SuperInput::JoyButton::x, 0);
    _inputs.addEvent("Pause", eng::SuperInput::JoyButton::start, 0);

    // KeyBoard inputs
    _inputs.addEvent("Move x", eng::SuperInput::Key::d);
    _inputs.addEvent("Move -x", eng::SuperInput::Key::q);
    _inputs.addEvent("Move y", eng::SuperInput::Key::s);
    _inputs.addEvent("Move -y", eng::SuperInput::Key::z);
    _inputs.addEvent("Move x", eng::SuperInput::Key::left);
    _inputs.addEvent("Move -x", eng::SuperInput::Key::right);
    _inputs.addEvent("Move y", eng::SuperInput::Key::down);
    _inputs.addEvent("Move -y", eng::SuperInput::Key::up);
    _inputs.addEvent("Fire", eng::SuperInput::Key::space);
    _inputs.addEvent("Pause", eng::SuperInput::Key::escape);

    // Mouse inputs
    _inputs.addEvent("MouseLeft", eng::SuperInput::MouseButton::left);
}

void rtp::Client::run()
{
    _setupInputs();
    systemsLoop();
    //disconnect();
}

void rtp::Client::disconnect()
{
    // Disconnect here
    std::cout << "[CLIENT][DISCONNECT] : send disconnect" << std::endl;
    boost::array<connectPayload_t, 1> dataTbs = {LEAVE_GAME};
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

int rtp::Client::connect(eng::RegistryManager &manager, bool multiplayer, int lvl)
{
    std::cout << "Connecting "  << multiplayer << " lvl = " << lvl << std::endl;
    rtp::Game game(_manager, _textureManager);
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT};
    boost::array<connectPayload_t, 1> dataRec;
    std::vector<int> res;
    std::cout << "adrress" << std::endl;


    //ICI adress

    dataTbs[0].addr1 = 0;
    dataTbs[0].addr2 = 0;
    dataTbs[0].addr3 = 0;
    dataTbs[0].addr4 = 0;
    dataTbs[0].port = _port;
    dataTbs[0].multiplayer = multiplayer;
    dataTbs[0].level = lvl;

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
    while (_gfx.isWindowOpen())
        _net.receiveData(_manager.getTop());
}

void rtp::Client::dataSend()
{
    while (_gfx.isWindowOpen())
        _net.sendData(_manager.getTop());
}

void rtp::Client::systemsLoop()
{
    rtp::ClientSystems systems(_gfx, "127.0.0.1", 3303, _socket, _inputs, _textureManager);
    std::function<int(eng::RegistryManager &, bool, int)> co = std::bind(&Client::connect, this, std::placeholders::_1,  std::placeholders::_2, std::placeholders::_3);
    rtp::MainMenu mm(_manager, co, _gfx, _textureManager);
    //rtp::PauseMenu pm(_manager, _gfx);
    std::stringstream ss;
    _gfx.setFrameRateLimit(60);
    _net.writeInChatBox(_manager.getTop(), ss.str(), rtp::NetworkSystems::ChatBoxStyle::EVENT);
    eng::PhysicSystems physics(_gfx.getDeltaSeconds());
    eng::AudioSystems sfx;

    while (_gfx.isWindowOpen()) {
        _inputs.updateEvents();
        _gfx.eventCatchWindow();
        
        // Receive Inputs
        systems.controlSystem(_manager.getTop(), _manager);

        // Update data
        systems.controlFireSystem(_manager.getTop());
        systems.controlChatSystem(_manager.getTop());
        systems.controlMovementSystem(_manager.getTop());
        systems.shootSystem(_manager.getTop());
        //physics.applyGravity(_manager.getTop());
        physics.applyVelocities(_manager.getTop());
        systems.limitPlayer(_manager.getTop());
        _gfx.animateSystem(_manager.getTop());
        systems.buttonStateSystem(_manager.getTop());
        systems.buttonSystem(_manager.getTop(), _manager);
        systems.backgroundSystem(_manager.getTop());
        systems.playerBullets(_manager.getTop());
        systems.killDeadEnemies(_manager.getTop());
        systems.killOutOfBounds(_manager.getTop());
        systems.killBullets(_manager.getTop());

        // Display & play sounds/music
        sfx.playMusic(_manager.getTop());
        sfx.playSound(_manager.getTop());
        _gfx.clear();
        _gfx.particleSystem(_manager.getTop());
        _gfx.drawSystem(_manager.getTop());
        _gfx.writeSystem(_manager.getTop());
        _gfx.display();
    }
    if (_receiveData.joinable()) {
        boost::array<networkPayload, 1> endmsg = {QUIT};
        _socket.send_to(boost::asio::buffer(endmsg),
        boost::asio::ip::udp::endpoint(boost::asio::ip::make_address("127.0.0.1"), _port));
        _receiveData.join();
    }
    if (_sendData.joinable()) {
        _sendData.join();
    }
    //net.disconnectSystems(r);
}
