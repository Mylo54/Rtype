/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#include "Client.hpp"

rtp::Client::Client(int port): _port(port)
{
    _manager.addRegistry("R1");
    _setupRegistry(_manager.getTop());
    eng::Entity player = _addPlayer(_manager.getTop());
    for (int i = 0; i < 10; i++)
        _addEnemy(_manager.getTop());
    _addBackgrounds(_manager.getTop());
    _openSocket();
}

rtp::Client::~Client()
{
}

void rtp::Client::run()
{
    // send();
    systemsLoop();
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
    reg.registerComponents(eng::SparseArray<rtp::EnemyStats>());
}

eng::Entity rtp::Client::_addPlayer(eng::Registry &reg)
{
    eng::Entity player = reg.spawnEntity();

    reg.addComponent<rtp::Position>(player, rtp::Position(200, 540, 0));
    reg.addComponent<rtp::Velocity>(player, rtp::Velocity());
    reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    reg.addComponent<rtp::Drawable>(player, rtp::Drawable("assets/player.png", 1, sf::IntRect(0, 0, 65, 49), 0.005));
    reg.addComponent<rtp::Controllable>(player, rtp::Controllable());

    return player;
}

eng::Entity rtp::Client::_addEnemy(eng::Registry &reg)
{
    eng::Entity enemy = reg.spawnEntity();
    float scale = (rand() % 10) + 1;

    reg.addComponent<rtp::Position>(enemy, rtp::Position(1920 + (rand() % 2000), rand() % 1080, 0));
    reg.addComponent<rtp::Velocity>(enemy, rtp::Velocity(-5, 0));
    reg.addComponent<rtp::Drawable>(enemy, rtp::Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.005));
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

//UDP
void rtp::Client::send()
{
    std::cout << "WAITING TO SEND\n";
    boost::array<networkPayload, 1> data_tbs = {CONNECT};
    _socket.send_to(boost::asio::buffer(data_tbs),
    boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), 3303});


    boost::array<networkPayload, 1> dataRec;
    boost::asio::ip::udp::endpoint endpoint;
    size_t len = this->_socket.receive_from(boost::asio::buffer(dataRec), endpoint);
    if (dataRec[0].ACTION_NAME == ACTIONTYPE_PREGAME::OK) {
        std::cout << "Connected to server" << std::endl;
    } else {
        send();
    }
}

void rtp::Client::_openSocket()
{
    _socket.open(boost::asio::ip::udp::v4());
}

void rtp::Client::systemsLoop()
{
    rtp::ClientSystems systems(std::vector<int>({1920, 1080, 32}), "RTYPE", "127.0.0.1", 3303, _socket);
    eng::Registry &r = _manager.getTop();
    
    // TODO: make the loop speed not depend on framerate

    while (systems.windowOpen()) {

        systems.eventCloseWindow();
        // Receive Inputs
        //systems.receiveData(r);
        systems.controlSystem(r);

        // Send new events
        systems.sendData(r);

        // Update data
        systems.controlFireSystem(r);
        systems.controlMovementSystem(r);
        systems.shootSystem(r);
        systems.positionSystem(r);
        systems.animateSystem(r);
        systems.playerBullets(r);
        systems.killDeadEnemies(r);

        //Display & play sounds
        systems.playSoundSystem(r);
        systems.clearSystem(r);
        systems.drawSystem(r);
        systems.backgroundSystem(r);
        systems.displaySystem(r);
    }
}

//port 3303