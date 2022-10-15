/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(boost::asio::ip::port_type port): _port(port), _socketTCP(_ioService), _socket(_ioContext, boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), port})
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    _addBackgrounds(_manager.getTop());
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
    systemsLoop();
    disconnect();
}

void rtp::Client::disconnect()
{
    // Disconnect here
    return;
}

std::vector<int> rtp::Client::connect()
{
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT};
    boost::array<connectPayload_t, 1> dataRec;
    std::vector<int> res;

    dataTbs[0].addr1 = 127;
    dataTbs[0].addr2 = 0;
    dataTbs[0].addr3 = 0;
    dataTbs[0].addr4 = 1;
    dataTbs[0].port = _port;
    //connection
    try {
        _socketTCP.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 3303));
        std::cout << "Client connect" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        res.push_back(1);
        return (res);
    }

    boost::asio::write(_socketTCP, boost::asio::buffer(dataTbs), _error);

    if (_error)
        std::cout << "send failed: " << _error.message() << std::endl;

    // getting response from server
    boost::asio::read(_socketTCP, boost::asio::buffer(dataRec), boost::asio::transfer_all(), _error);
    res.push_back(0);
    res.push_back(dataRec[0].playerId);
    res.push_back(dataRec[0].syncId);
    if (_error && _error != boost::asio::error::eof) {
        std::cout << "receive failed: " << _error.message() << std::endl;
    } else {
        std::cout << "action receive number : " << dataRec[0].ACTION_NAME << std::endl;
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
    reg.addComponent<rtp::Drawable>(player, rtp::Drawable("assets/players.png", 1, sf::IntRect(0, ((playerId - 1) * 49), 60, 49), 0.10));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
    reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
    reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));

    std::cout << "You are player " << playerId << std::endl;
    std::cout << "rect: " << ((playerId - 1) * 49) << std::endl;
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

std::vector<eng::Entity> rtp::Client::_addBackgrounds(eng::Registry &reg)
{
    eng::Entity fg1 = reg.spawnEntity();
    eng::Entity fg2 = reg.spawnEntity();
    eng::Entity mg1 = reg.spawnEntity();
    eng::Entity mg2 = reg.spawnEntity();
    eng::Entity bg1 = reg.spawnEntity();
    eng::Entity bg2 = reg.spawnEntity();
    std::vector<eng::Entity> bgs = {fg1, fg2, mg1, mg2, bg1, bg2};

    // Foregrounds
    reg.addComponent<rtp::Position>(fg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(fg1, rtp::Velocity(-20, 0));
    reg.addComponent<rtp::Background>(fg1, rtp::Background("assets/foreground.png"));
    reg.addComponent<rtp::Position>(fg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(fg2, rtp::Velocity(-20, 0));
    reg.addComponent<rtp::Background>(fg2, rtp::Background("assets/foreground.png"));

    // Middlegrounds
    reg.addComponent<rtp::Position>(mg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(mg1, rtp::Velocity(-10, 0));
    reg.addComponent<rtp::Background>(mg1, rtp::Background("assets/middleground.png"));
    reg.addComponent<rtp::Position>(mg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(mg2, rtp::Velocity(-10, 0));
    reg.addComponent<rtp::Background>(mg2, rtp::Background("assets/middleground.png"));
    
    // Backgrounds
    reg.addComponent<rtp::Position>(bg1, rtp::Position(0, 0, 0));
    reg.addComponent<rtp::Velocity>(bg1, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Background>(bg1, rtp::Background("assets/background.png"));
    reg.addComponent<rtp::Position>(bg2, rtp::Position(1920, 0, 0));
    reg.addComponent<rtp::Velocity>(bg2, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Background>(bg2, rtp::Background("assets/background.png"));
    return bgs;
}

void rtp::Client::systemsLoop()
{
    rtp::ClientSystems systems(std::vector<int>({1920, 1080, 32}), "RTYPE", "127.0.0.1", 3303, _socket);
    eng::Registry &r = _manager.getTop();
    systems.setMaxFrameRate(60);

    while (systems.windowOpen()) {
        systems.eventCloseWindow();
        // Receive Inputs
        systems.updDeltaTime();
        systems.controlSystem(r);
        systems.receiveData(r);

        // Send new events
        systems.sendData(r);

        // Update data
        systems.controlFireSystem(r);
        systems.controlChatSystem(r);
        systems.controlMovementSystem(r);
        systems.shootSystem(r);
        systems.positionSystem(r);
        systems.limitPlayer(r);
        systems.animateSystem(r);
        systems.playerBullets(r);
        systems.killDeadEnemies(r);

        //Display & play sounds
        systems.playSoundSystem(r);
        systems.clearSystem(r);
        systems.drawSystem(r);
        systems.writeSystem(r);
        systems.backgroundSystem(r);
        systems.displaySystem(r);
    }
}