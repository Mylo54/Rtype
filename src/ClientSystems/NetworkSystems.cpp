/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** NetworkSystems
*/

#include "NetworkSystems.hpp"

rtp::NetworkSystems::NetworkSystems(std::string address, int port,
boost::asio::ip::udp::socket &socket, sf::Time &delta):
_socket(socket), _delta(delta)
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
    boost::array<inputPayload_t, 1UL> data;

    for (int i = 0; i < controllables.size() && i < synceds.size(); i++) {
        auto ctrl = controllables[i];
        auto sync = synceds[i];

        if (ctrl.has_value() && sync.has_value()) {
            data[0].syncId = sync.value().id;
            if (ctrl.value().shoot) {
                data[0].ACTION_NAME = SHOT;
                _socket.send_to(boost::asio::buffer(data), _endpoint);
            }
            if (ctrl.value().xAxis > 0)
                data[0].ACTION_NAME = RIGHT;
            else if (ctrl.value().xAxis < 0)
                data[0].ACTION_NAME = LEFT;
            else
                data[0].ACTION_NAME = XSTILL;
            _socket.send_to(boost::asio::buffer(data), _endpoint);
            if (ctrl.value().yAxis > 0)
                data[0].ACTION_NAME = DOWN;
            else if (ctrl.value().yAxis < 0)
                data[0].ACTION_NAME = UP;
            else
                data[0].ACTION_NAME = YSTILL;
            _socket.send_to(boost::asio::buffer(data), _endpoint);
        }
    }
}

// interpolate two vectors with O=0
float interpolate(float a, float b)
{
    float res = 0;

    res = fabs(a - b);
    res += fmin(a, b);
    if (a <= 0 && b <= 0)
        res = -res;
    return res;
}

float midlerp(float a, float b)
{
    return a + 0.5 * (b - a);
}

void interpolatePos(eng::Registry &r, int e, eng::Position nP)
{
    try {
        auto p = r.getComponents<eng::Position>()[e].value();

        r.emplaceComponent<eng::Position>(eng::Entity(e),
        eng::Position(midlerp(p.x, nP.x), midlerp(p.y, nP.y), midlerp(p.z, nP.z)));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Position>(eng::Entity(e), eng::Position(nP.x, nP.y, nP.z));
    }
}

void interpolateVel(eng::Registry &r, int e, eng::Velocity nP)
{
    try {
        auto p = r.getComponents<eng::Velocity>()[e].value();

        r.emplaceComponent<eng::Velocity>(eng::Entity(e),
        eng::Velocity(midlerp(p.x, nP.x), midlerp(p.y, nP.y)));
    } catch (std::bad_optional_access &error) {
        r.addComponent<eng::Velocity>(eng::Entity(e), eng::Velocity(nP.x, nP.y));
    }
}

void rtp::NetworkSystems::oldReceiveData(eng::Registry &r)
{
    int e = 0;
    bool toBuild = false;
    bool start = false;

    while (true) {
        while (!start) {
            _socket.receive(boost::asio::buffer(_dataBuffer));
            if (_dataBuffer[0].COMPONENT_NAME == END_PACKET) {
                start = true;
            }
        }
        _socket.receive(boost::asio::buffer(_dataBuffer));
        if (_dataBuffer[0].COMPONENT_NAME == END_PACKET)
            return;
        auto &data = _dataBuffer[0];
        e = _getSyncedEntity(r, data.syncId);
        toBuild = false;
        if (e == -1) {
            toBuild = true;
            e = r.spawnEntity().getId();
            r.addComponent<Synced>(eng::Entity(e), Synced(data.syncId));
        }
        if (_dataBuffer[0].COMPONENT_NAME == POSITION)
            //r.emplaceComponent<Position>(eng::Entity(e), Position(data.valueA, data.valueB, data.valueC));
            interpolatePos(r, e, eng::Position(data.valueA, data.valueB, data.valueC));
        if (_dataBuffer[0].COMPONENT_NAME == VELOCITY)
            r.emplaceComponent<eng::Velocity>(eng::Entity(e), eng::Velocity(data.valueA, data.valueB));
        if (data.COMPONENT_NAME == ENEMY_STATS) {
            r.emplaceComponent<EnemyStats>(eng::Entity(e), EnemyStats(data.valueB, data.valueA));
            if (toBuild)
                _completeEnemy(r, e);
        }
        if (data.COMPONENT_NAME == BONUS) {
            r.emplaceComponent<Bonus>(eng::Entity(e), Bonus(data.valueA));
            if (toBuild)
                _completeBonus(r, e);
        }
        if (data.COMPONENT_NAME == PLAYER_STATS) {
            r.emplaceComponent<PlayerStats>(eng::Entity(e), PlayerStats(data.valueA, data.valueB, data.valueC));
            if (toBuild)
                _completePlayer(r, e);
            if (data.syncId != _mySyncId)
                r.getComponents<Shooter>()[e].value().shoot = data.shot;
        }
    }
}

static void setupBuffer(std::vector<int> &buffer, size_t size)
{
    for (int i = 0; i < size / 4; i++)
        buffer.push_back(0);
}

// TODO: fix this
void rtp::NetworkSystems::receiveData(eng::Registry &r)
{
    size_t availableSize = 0;
    int bodySize = 0;
    std::vector<int> buffer;
    int current = 0;
    bool toBuild = false;
    
    // Get Packet
    _socket.wait(boost::asio::socket_base::wait_type::wait_read);
    availableSize = _socket.available();
    buffer.clear();
    setupBuffer(buffer, availableSize);
    _socket.receive(boost::asio::buffer(buffer));
    
    // Analyse Packet
    auto it = buffer.begin();
    // Throw invalid packet
    if (*it != 1405)
        return;
    it++;
    bodySize = *it;
    it++;
    for (int i = 0; i < bodySize; i++, it++) {
        if (*it == 2002) {
            it++;
            current = _getSyncedEntity(r, *(++it));
            toBuild = (current == -1);
            if (toBuild) {
                current = r.spawnEntity().getId();
                r.emplaceComponent<Synced>(eng::Entity(current), Synced(*it));
            }
        }
        if (*it == POSITION) {
            std::cout << "Position" << std::endl;
            interpolatePos(r, current, eng::Position(*(++it), *(++it), *(++it)));it++;
        }
        if (*it == VELOCITY)
            interpolateVel(r, current, eng::Velocity(*(++it), *(++it), *(++it)));
        if (*it == ENEMY_STATS) {
            r.emplaceComponent(current, EnemyStats(*(++it), *(++it)));
            if (toBuild)
                _completeEnemy(r, current);
        }
        if (*it == PLAYER_STATS) {
            r.emplaceComponent(current, PlayerStats(*(++it), *(++it), *(++it)));it++;
            if (toBuild)
                _completePlayer(r, current);
        }
        if (*it == BONUS) {
            r.emplaceComponent(current, Bonus(*(++it)));
            if (toBuild)
                _completeBonus(r, current);
        }
    }
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
        r.emplaceComponent<eng::Drawable>(eng::Entity(e), eng::Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.005));
        r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40 * scale, 16 * scale));
        r.getComponents<eng::Drawable>()[e].value().sprite.setScale(scale, scale);
    }
}

void rtp::NetworkSystems::_completeBonus(eng::Registry &r, int e)
{
    int type = r.getComponents<Bonus>()[e].value().type;
    float scale = 1;
    if (type == 0) {
        scale = 1;
        r.emplaceComponent<eng::Drawable>(eng::Entity(e), eng::Drawable("assets/bonus.png", 1, sf::IntRect(0, 0, 50, 50), 0.010));
        r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(16 * scale, 16 * scale));
        r.getComponents<eng::Drawable>()[e].value().sprite.setScale(scale, scale);
    }
}

void rtp::NetworkSystems::_completePlayer(eng::Registry &r, int e)
{
    int playerId = r.getComponents<PlayerStats>()[e].value().playerId;
    sf::IntRect rect = {0, 0, 60, 49};
    r.addComponent<rtp::Shooter>(eng::Entity(e), rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40, 16));
    if (playerId == 2)
        rect.top = 49;
    if (playerId == 3)
        rect.top = 98;
    if (playerId == 4)
        rect.top = 147;
    r.addComponent<eng::Drawable>(eng::Entity(e), eng::Drawable("assets/players.png", 1, rect, 0.10));

    std::stringstream ss;
    ss << "Player " << playerId << " joined the game!";
    writeInChatBox(r, ss.str(), EVENT);
}

void rtp::NetworkSystems::disconnectSystems(eng::Registry &r)
{
    auto &synceds = r.getComponents<Synced>();
    boost::array<inputPayload_t, 1UL> data;

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
