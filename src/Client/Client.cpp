/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(boost::asio::ip::port_type port): _port(port), _socketTCP(_ioService), _socket(_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("0.0.0.0"), port})
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addBackgrounds(_manager.getTop());
    _addScore(_manager.getTop());
    std::cout << "My address: <" << _socket.local_endpoint().address() << ":";
    std::cout << _socket.local_endpoint().port() << ">" << std::endl;
}

rtp::Client::~Client()
{
}

void rtp::Client::run()
{
    std::vector<int> c = connect();

    if (c[0] == 1)
        return;
    eng::Entity player = _addPlayer(_manager.getTop(), c[1], c[2]);
    _mySyncId = c[2];
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

std::vector<int> rtp::Client::connect()
{
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

    boost::asio::ip::tcp::resolver resolver(_ioService);

    char* serverName = "localhost";


    boost::asio::ip::tcp::resolver::query query(serverName, "daytime");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

    try {
        _socketTCP.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address("0.0.0.0"), 3303));
        std::cout << "[Client][Connect]: connect success" << std::endl;
        std::cout << "[Client][Connect]: addresse : " << dataTbs[0].addr1 << "." << dataTbs[0].addr2 << "." << dataTbs[0].addr3 << "." << dataTbs[0].addr4 << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        res.push_back(1);
        return (res);
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
    return (res);
}

void rtp::Client::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    reg.registerComponents(eng::SparseArray<rtp::AudioSource>());
    reg.registerComponents(eng::SparseArray<rtp::Bullet>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::RectCollider>());
    reg.registerComponents(eng::SparseArray<rtp::PlayerStats>());
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
    reg.registerComponents(eng::SparseArray<rtp::Writable>());
    reg.registerComponents(eng::SparseArray<rtp::Synced>());
}

eng::Entity rtp::Client::_addPlayer(eng::Registry &reg, int playerId, int syncId)
{
    eng::Entity player = reg.spawnEntity();

    reg.addComponent<rtp::Position>(player, rtp::Position(200, 540, 0));
    reg.addComponent<rtp::Velocity>(player, rtp::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    reg.addComponent<rtp::Drawable>(player, rtp::Drawable("assets/players.png", 1, rect, 0.10));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));

    std::cout << "You are player " << playerId << std::endl;
    return player;
}

eng::Entity rtp::Client::_addEnemy(eng::Registry &reg)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    reg.addComponent<rtp::Position>(enemy, rtp::Position(1920 + (rand() % 2000), rand() % 1080, 0));
    reg.addComponent<rtp::Velocity>(enemy, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Drawable>(enemy, rtp::Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.10));
    reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
    reg.addComponent<rtp::RectCollider>(enemy, rtp::RectCollider(40*scale, 16*scale));

    reg.getComponents<rtp::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
    return enemy;
}

void rtp::Client::_addScore(eng::Registry &reg)
{
    eng::Entity score = reg.spawnEntity();

    reg.addComponent<rtp::Position>(score, rtp::Position(1000, 0, 0));
    reg.addComponent<rtp::Writable>(score, rtp::Writable("score", "SCORE:000 000"));
}

void rtp::Client::_addBackgrounds(eng::Registry &reg)
{
    for (int i = 0; i < 6; i++) {
        eng::Entity bg = reg.spawnEntity();
        reg.addComponent<rtp::Position>(bg, rtp::Position((i % 2) * 1920, 0, 0));
        if (i < 2) {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-20, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/foreground.png"));
        } else if (i < 4) {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-10, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/middleground.png"));
        } else {
            reg.addComponent<rtp::Velocity>(bg, rtp::Velocity(-5, 0));
            reg.addComponent<rtp::Background>(bg, rtp::Background("assets/background.png"));
        }
    }
}

void rtp::Client::systemsLoop()
{
    rtp::GraphicsSystems gfx(std::vector<int>({1920, 1080, 32}), "RTYPE");
    rtp::NetworkSystems net("127.0.0.1", 3303, _socket, _mySyncId, gfx.getDelta());
    rtp::ClientSystems systems(gfx.getWindow(), gfx.getClock(), gfx.getDelta(), "127.0.0.1", 3303, _socket);
    eng::Registry &r = _manager.getTop();
    gfx.setMaxFrameRate(60);

    while (gfx.windowOpen()) {
        gfx.eventCatchWindow();
        
        // Receive Inputs
        gfx.controlSystem(r);
        net.receiveData(r);

        // Send new events
        net.sendData(r);

        // Update data
        systems.controlFireSystem(r);
        systems.controlChatSystem(r);
        systems.controlMovementSystem(r);
        systems.shootSystem(r);
        systems.positionSystem(r);
        systems.limitPlayer(r);
        gfx.animateSystem(r);
        systems.playerBullets(r);
        systems.killDeadEnemies(r);
        systems.killBullets(r);

        // Display & play sounds
        systems.playSoundSystem(r);
        gfx.clearSystem();
        gfx.backgroundSystem(r);
        gfx.drawSystem(r);
        gfx.writeSystem(r);
        gfx.displaySystem();
    }
    net.disconnectSystems(r);
}