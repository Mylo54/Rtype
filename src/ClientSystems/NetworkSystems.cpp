/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkSystems
*/

#include "NetworkSystems.hpp"

rtp::NetworkSystems::NetworkSystems(std::string address, int port,
boost::asio::ip::udp::socket &socket, sf::Time &delta,
eng::TextureManager &textureManager):
_socket(socket), _delta(delta), _textureManager(textureManager)
{
    _endpoint = {boost::asio::ip::make_address(address), static_cast<boost::asio::ip::port_type>(port)};
}

rtp::NetworkSystems::~NetworkSystems()
{
}

void rtp::NetworkSystems::setSyncId(int id)
{
    _mySyncId = id;
}

void rtp::NetworkSystems::setDelta(sf::Time &delta)
{
    _delta = delta;
}

void rtp::NetworkSystems::sendData(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();
    auto &synceds = r.getComponents<Synced>();
    std::vector<int> payload;

    payload.push_back(1450);
    payload.push_back(0);
    for (int i = 0; i < controllables.size() && i < synceds.size(); i++) {
        if (controllables[i].has_value() && synceds[i].has_value()) {
            auto &ctrl = controllables[i].value();

            payload.push_back(2002);
            payload.push_back(synceds[i].value().id);
            payload.push_back(ctrl.xAxis);
            payload.push_back(ctrl.yAxis);
            payload.push_back(ctrl.shoot);
            payload[1] += 5;
        }
    }
    _socket.send_to(boost::asio::buffer(payload), _endpoint);
}

static float midlerp(float a, float b)
{
    return a + 0.5 * (b - a);
}

static void setupBuffer(std::vector<int> &buffer, size_t size)
{
    for (int i = 0; i < size / 4; i++)
        buffer.push_back(0);
}

static void emplacePosition(eng::Registry &r, int e, std::vector<int> &b, int &i)
{
    if (i >= b[1] || b[i] != rtp::COMPONENTS_SYNCED::POSITION)
        return;
    try {
        auto p = r.getComponents<eng::Position>()[e].value();

        r.emplaceComponent<eng::Position>(eng::Entity(e),
        eng::Position(midlerp(p.x, b[i+1]), midlerp(p.y, b[i+2]), midlerp(p.z, b[i+3])));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Position>(eng::Entity(e), eng::Position(b[i+1], b[i+2], b[i+3]));
    }
    i += 5;
}

static void emplaceVelocity(eng::Registry &r, int e, std::vector<int> &b, int &i)
{
    if (i >= b[1] || b[i] != rtp::COMPONENTS_SYNCED::VELOCITY)
        return;
    try {
        auto p = r.getComponents<eng::Velocity>()[e].value();

        r.emplaceComponent<eng::Velocity>(eng::Entity(e),
        eng::Velocity(midlerp(p.x, b[i+1]), midlerp(p.y, b[i+2])));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Velocity>(eng::Entity(e), eng::Velocity(b[i+1], b[i+2]));
    }
    i += 4;
}

void rtp::NetworkSystems::_emplaceEnemy(eng::Registry &r, int e,
std::vector<int> &b, int &i, bool toBuild)

{
    if (i >= b[1] || b[i] != ENEMY_STATS)
        return;
    r.emplaceComponent<EnemyStats>(e, EnemyStats(b[i+1], b[i+2]));
    if (toBuild)
        _completeEnemy(r, e);
    i += 3;
}

void rtp::NetworkSystems::_emplacePlayer(eng::Registry &r, int e,
std::vector<int> &b, int &i, bool toBuild)
{
    if (i >= b[1] || b[i] != PLAYER_STATS)
        return;
    r.emplaceComponent<PlayerStats>(e, PlayerStats(b[i+1], b[i+2], b[i+3]));
    if (toBuild)
        _completePlayer(r, e);
    i += 5;
}

void rtp::NetworkSystems::_emplaceBonus(eng::Registry &r, int e,
std::vector<int> &b, int &i, bool toBuild)
{
    if (i >= b[1] || b[i] != BONUS)
        return;
    r.emplaceComponent<Bonus>(e, Bonus(b[i+1]));
    if (toBuild)
        _completeBonus(r, e);
    i += 2;
}

void rtp::NetworkSystems::receiveData(eng::Registry &r)
{
    std::vector<int> buffer;
    int current = 0;
    bool toBuild = false;
    
    // Get Packet
    _socket.wait(boost::asio::socket_base::wait_type::wait_read);
    setupBuffer(buffer, _socket.available());
    _socket.receive(boost::asio::buffer(buffer));
    
    // Throw invalid packets
    if (buffer[0] != 1405)
        return;
    for (int i = 2; i < buffer[1];) {
        if (i < buffer[1] && buffer[i] == 2002) {
            current = _getSyncedEntity(r, buffer[i+1]);
            toBuild = (current == -1);
            if (toBuild) {
                current = r.spawnEntity().getId();
                r.emplaceComponent<Synced>(eng::Entity(current), Synced(buffer[i+1]));
            }
            i+=2;
        }
        emplacePosition(r, current, buffer, i);
        emplaceVelocity(r, current, buffer, i);
        _emplaceEnemy(r, current, buffer, i, toBuild);
        _emplacePlayer(r, current, buffer, i, toBuild);
        _emplaceBonus(r, current, buffer, i, toBuild);
    }
    return;
}

int rtp::NetworkSystems::_getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<Synced>();

    for (int i = 0; i < synceds.size(); i++)
        if (synceds[i].has_value())
            if (synceds[i].value().id == syncId)
                return (i);
    return (-1);
}

void rtp::NetworkSystems::_completeEnemy(eng::Registry &r, int e)
{
    int type = r.getComponents<EnemyStats>()[e].value().enemyType;
    float scale = 1;
    if (type == 0) {
        scale = 3;
        r.emplaceComponent<eng::Drawable>(eng::Entity(e), eng::Drawable(_textureManager.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.005));
        r.emplaceComponent<eng::RectCollider>(eng::Entity(e), eng::RectCollider(40 * scale, 16 * scale));
        r.getComponents<eng::Drawable>()[e].value().sprite.setScale(scale, scale);
    }
}

void rtp::NetworkSystems::_completeBonus(eng::Registry &r, int e)
{
    int type = r.getComponents<Bonus>()[e].value().type;
    float scale = 1;
    if (type == 0) {
        scale = 1;
        r.emplaceComponent<eng::Drawable>(eng::Entity(e), eng::Drawable(_textureManager.getTextureFromFile("assets/bonus.png"), 1, sf::IntRect(0, 0, 50, 50), 0.010));
        r.emplaceComponent<eng::RectCollider>(eng::Entity(e), eng::RectCollider(16 * scale, 16 * scale));
        r.getComponents<eng::Drawable>()[e].value().sprite.setScale(scale, scale);
    }
}

void rtp::NetworkSystems::_completePlayer(eng::Registry &r, int e)
{
    int playerId = r.getComponents<PlayerStats>()[e].value().playerId;
    sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
    r.addComponent<rtp::Shooter>(eng::Entity(e), rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    r.emplaceComponent<eng::RectCollider>(eng::Entity(e), eng::RectCollider(40, 16));
    auto &smoke = r.addComponent<eng::ParticleEmitter>(eng::Entity(e), eng::ParticleEmitter())[e].value();
    r.addComponent<eng::RigidBody>(eng::Entity(e), eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));

    smoke.setParticleTexture(eng::PARTICLE_TYPE::Sprite, "assets/smokeParticle.png");
    smoke.setBaseSpeed(500, 1000);
    smoke.setLifetime(5);
    smoke.setBaseRotation(260, 280);
    smoke.setEmittingRate(0.01);
    smoke.setMaxNumber(100);
    smoke.isLocal = false;
    smoke.setParticleColor(100, 100, 100, 100);
    r.addComponent<eng::Drawable>(eng::Entity(e), eng::Drawable(_textureManager.getTextureFromFile("assets/players.png"), 1, rect, 0.10));

    std::stringstream ss;
    ss << "Player " << playerId << " joined the game!";
    writeInChatBox(r, ss.str(), EVENT);
}

void rtp::NetworkSystems::disconnectSystems(eng::Registry &r)
{
    auto &synceds = r.getComponents<Synced>();
    boost::array<connectPayload_t, 1UL> data;

    for (int i = 0; i < synceds.size(); i++) {
        auto sync = synceds[i];
        if (sync.has_value()) {
            data[0].syncId = sync.value().id;
            data[0].ACTION_NAME = LEAVE_GAME;
            _socket.send_to(boost::asio::buffer(data), _endpoint);
            std::cout << "[CLIENT][DISCONNECT] : send disconnect" << std::endl;

        }
    }
}

void rtp::NetworkSystems::setText(eng::Registry &r, std::string message, std::optional<eng::Writable> &wrt,  rtp::NetworkSystems::ChatBoxStyle style)
{
    if (wrt.has_value()) {
        wrt.value()._txt.setStyle(sf::Text::Bold);
        wrt.value()._txt.setString(message);
    }
}

void rtp::NetworkSystems::setText(eng::Registry &r, std::string message, std::string name,  rtp::NetworkSystems::ChatBoxStyle style)
{
    auto &writables = r.getComponents<eng::Writable>();

    for (int i = 0; i < writables.size(); i++) {
        auto &wrt = writables[i];
        if (wrt.has_value() && wrt.value()._name == name) {
            wrt.value()._txt.setString(message);
            if (style == NetworkSystems::CHAT) {
                wrt.value()._txt.setStyle(sf::Text::Regular);
                wrt.value()._txt.setFillColor(sf::Color::White);
            }
            if (style == NetworkSystems::EVENT) {
                wrt.value()._txt.setStyle(sf::Text::Italic);
                wrt.value()._txt.setFillColor(sf::Color::Blue);
            }
        }
    }
}

void rtp::NetworkSystems::writeInChatBox(eng::Registry &r, std::string message, rtp::NetworkSystems::ChatBoxStyle style)
{
    auto &writables = r.getComponents<eng::Writable>();
    auto &positions = r.getComponents<eng::Position>();

    // Move all chat line up and change their name
    for (int i = 5; i > 0; i--) {
        for (int j = 0; j < writables.size(); j++) {
            auto &wrt = writables[j];
            std::stringstream toFind;
            std::stringstream newName;
            toFind << "ChatBox" << i;
            newName << "ChatBox" << (i + 1);
            if (wrt.has_value() && wrt.value()._name == toFind.str()) {
                // condition to delete
                if (i == 5) {
                    r.killEntity(eng::Entity(j));
                    break;
                }
                if (positions[j].has_value()) positions[j].value().y -= 30;
                wrt.value()._name = newName.str();
                break;
            }
        }
    }
    // Create ChatBox1
    addChatBox(r);
    // Write in ChatBox1
    setText(r, message, "ChatBox1", style);
}

void rtp::NetworkSystems::addChatBox(eng::Registry &reg)
{
    eng::Entity chatBox = reg.spawnEntity();

    reg.addComponent<eng::Writable>(chatBox, eng::Writable("ChatBox1"));
    reg.addComponent<eng::Position>(chatBox, eng::Position(0, 980, 0));
}

std::vector<int> rtp::NetworkSystems::connect(int port)
{
    boost::array<demandConnectPayload_s, 1> dataTbs = {CONNECT};
    boost::array<connectPayload_t, 1> dataRec;
    std::vector<int> res;
    boost::asio::io_context ioContext;

    //ICI adress

    dataTbs[0].addr1 = 0;
    dataTbs[0].addr2 = 0;
    dataTbs[0].addr3 = 0;
    dataTbs[0].addr4 = 0;
    dataTbs[0].port = port;

    //connection

    boost::asio::ip::tcp::resolver resolver(ioContext);

    std::string serverName = "localhost";

    boost::asio::ip::tcp::resolver::query query("0.0.0.0", "3303");
    boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
    boost::asio::ip::tcp::resolver::iterator end;

    boost::asio::ip::tcp::socket socketTCP{ioContext};
    boost::system::error_code error;

    try {

        boost::system::error_code error = boost::asio::error::host_not_found;
        socketTCP.connect(*(resolver.resolve(query)), error);
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
        return (res);
    }

    boost::asio::write(socketTCP, boost::asio::buffer(dataTbs), error);

    if (error)
        std::cout << "[Client][Connect]: send failed: " << error.message() << std::endl;

    // getting response from server
    boost::asio::read(socketTCP, boost::asio::buffer(dataRec), boost::asio::transfer_all(), error);
    res.push_back(0);
    res.push_back(dataRec[0].playerId);
    res.push_back(dataRec[0].syncId);
    if (error && error != boost::asio::error::eof) {
        std::cout << "[Client][Connect]: receive failed: " << error.message() << std::endl;
    } else {
        std::cout << "[Client][Connect]:action receive number : " << dataRec[0].ACTION_NAME << std::endl;
    }
    _mySyncId = res[2];
    return (res);
}
