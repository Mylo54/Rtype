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
    _addPlayer(_manager.getTop());
    _addBackgrounds(_manager.getTop());
}

rtp::Client::~Client()
{
}

void rtp::Client::run()
{
    systemsLoop();
}

void rtp::Client::_setupRegistry(eng::Registry &reg)
{
    reg.registerComponents(eng::SparseArray<rtp::Position>());
    reg.registerComponents(eng::SparseArray<rtp::Velocity>());
    reg.registerComponents(eng::SparseArray<rtp::Drawable>());
    reg.registerComponents(eng::SparseArray<rtp::Controllable>());
    reg.registerComponents(eng::SparseArray<rtp::Shooter>());
    reg.registerComponents(eng::SparseArray<rtp::Background>());
    reg.registerComponents(eng::SparseArray<rtp::AudioSource>());
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

    boost::asio::io_context io_context;
    boost::asio::ip::udp::socket socket{io_context};
    socket.open(boost::asio::ip::udp::v4());

    boost::array<networkPayload, 1> data_tbs = {DOWN};
    socket.send_to(boost::asio::buffer(data_tbs),
    boost::asio::ip::udp::endpoint{boost::asio::ip::make_address("127.0.0.1"), 3303});
}

void rtp::Client::systemsLoop()
{
    sf::RenderWindow w(sf::VideoMode(1920, 1080, 32), "RTYPE");
    sf::Clock c;
    rtp::ClientSystems systems(w, c);
    eng::Registry &r = _manager.getTop();
    
    // TODO: make the loop speed not depend on framerate
    w.setFramerateLimit(60);

    while (w.isOpen()) {

        // TODO: make this a system or something, this needs to go out
        //////////////////////////////////////////////////////////////
        sf::Event event;
        while (w.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                w.close();
        }
        //////////////////////////////////////////////////////////////

        // Receive Inputs
        //systems.receiveData(r);
        systems.controlSystem(r);

        // Send new events
        //systems.sendData(r);

        // Update data
        systems.controlFireSystem(r);
        systems.controlMovementSystem(r);
        systems.shootSystem(r);
        systems.positionSystem(r);
        systems.animateSystem(r);

        //Display & play sounds
        systems.playSoundSystem(r);
        systems.clearSystem(r);
        systems.drawSystem(r);
        systems.backgroundSystem(r);
        systems.displaySystem(r);
    }
}

//port 3303