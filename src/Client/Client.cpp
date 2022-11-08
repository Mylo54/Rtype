/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(): _graphics(1920, 1080, "Super R-Type"),
_inputs(_graphics.getRenderWindow()), _physics(_graphics.getDeltaSeconds())
{
    std::cout << "Client has been created" << std::endl;
}

rtp::Client::~Client()
{
}

int rtp::Client::connect(eng::RegistryManager &manager, bool multiplayer, int lvl, int map)
{
    std::cout << "Connecting "  << multiplayer << " lvl = " << lvl << std::endl;
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
    if (multiplayer == false) {
        rtp::Game game(_manager, _textureManager);
        eng::Entity player = game.addPlayer(_manager.getTop(), res[1], res[2]);
    } else {
        rtp::Game game(_manager, _textureManager);
        std::cout << "multiplayer before connection screen" << std::endl;
        //rtp::Connection connection(_manager, _textureManager);
        eng::Entity player = game.addPlayer(_manager.getTop(), res[1], res[2]);
    }
    _myPlayerId = res[1];
    _mySyncId = res[2];
    _net.setSyncId(_mySyncId);
    _receiveData = std::thread(&rtp::Client::dataReception, this);
    _sendData = std::thread(&rtp::Client::dataSend, this);

    return (0);
}

rtp::scene_package_t rtp::Client::_makePackage()
{
    scene_package_t pkg = {_registries.getTop(), _graphics, _physics, _audio,
        _net, _inputs, _textures};

    return (pkg);
}

int rtp::Client::run()
{
    _sceneEvent = sceneEvent::none;
    _sceneNumber = sceneNumber::menu;
    _registries.addRegistry("start");
    // rtp::AScene defaultScene(_makePackage());
    std::function<int(eng::RegistryManager &, bool, int, int)> co = std::bind(&Client::connect, this, std::placeholders::_1,  std::placeholders::_2, std::placeholders::_3, std::placeholders::_4);
    rtp::MainMenu defaultScene(_makePackage(), _registries, co);
    _scenes.push(&defaultScene);

    std::cout << "Client is up!" << std::endl;
    defaultScene.setupRegistry();
    while (_graphics.isWindowOpen() && !_scenes.empty()) {
        _scenes.top()->systemRun();

        // change scene & registry when event asks for;
        if (_sceneEvent == rtp::sceneEvent::pushScene) {
            _registries.addRegistry("new");
            //scenes.push(askedscene);
        }
        if (_sceneEvent == rtp::sceneEvent::popScene) {
            _registries.popRegistry();
            _scenes.pop();
        }
    }
    return (0);
}
