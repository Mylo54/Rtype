/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystems
*/

#include "ClientSystems.hpp"

rtp::ClientSystems::ClientSystems(std::vector<int> dimWdw, std::string nameWdw, std::string adress, int port, boost::asio::ip::udp::socket &socket) : _w(sf::RenderWindow(sf::VideoMode(dimWdw[0], dimWdw[1], dimWdw[2]), nameWdw)), _c(sf::Clock()), _socket(socket)
{
    _displayTime = 0;
    
    _endpoint = {boost::asio::ip::make_address(adress), static_cast<boost::asio::ip::port_type>(port)};
    _w.setFramerateLimit(60);
}

rtp::ClientSystems::~ClientSystems()
{
}

void rtp::ClientSystems::logSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            std::cout << i << ": pos = {" << pos.value().x << ", " << pos.value().y;
            std::cout << ", " << pos.value().z << "}, vel = {" << vel.value().x;
            std::cout << ", " << vel.value().y << "}" << std::endl;
        }
    }
}

void rtp::ClientSystems::controlSystem(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            // up and down
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                ctrl.value().yAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                ctrl.value().yAxis = 1;
            else
                ctrl.value().yAxis = 0;
            
            // left and right
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                ctrl.value().xAxis = -1;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                ctrl.value().xAxis = 1;
            else
                ctrl.value().xAxis = 0;
            
            // shoot
            ctrl.value().shoot = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);
            // ctrl.value().chat = sf::Event::KeyReleased()
            // ctrl.value().chat = sf::Keyboard::isKeyPressed(sf::Keyboard::C);
            // ctrl.value().event = sf::Keyboard::isKeyPressed(sf::Keyboard::V);
            // ctrl.value().event = sf::Event::KeyReleased;
        }
    }
}

void rtp::ClientSystems::controlMovementSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * 2;
            vel.value().x += (vel.value().x > 0) ? -1 : 0;
            vel.value().x += (vel.value().x < 0) ? 1 : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * 2;
            vel.value().y += (vel.value().y > 0) ? -1 : 0;
            vel.value().y += (vel.value().y < 0) ? 1 : 0;
        }
    }
}

void rtp::ClientSystems::clearSystem(eng::Registry &r)
{
    _w.clear();
}

void rtp::ClientSystems::displaySystem(eng::Registry &r)
{
    if ((_delta.asSeconds() + _displayTime) >= (1/60)) {
        _w.display();
        _displayTime = _delta.asSeconds() + _displayTime - (1/60);
    }
}

// Some changes to optimize would be good
void rtp::ClientSystems::animateSystem(eng::Registry &r)
{
    auto &sprites = r.getComponents<Drawable>();

    for (int i = 0; i < sprites.size(); i++) {
        auto &spr = sprites[i];

        if (spr.has_value()) {
            sf::IntRect rect = spr.value().sprite.getTextureRect();
            if (spr.value().sheetDirection != 0) {
                spr.value().nextFrame -= _delta.asSeconds();
            }
            // Animate to the right
            if (spr.value().sheetDirection == 1 && spr.value().nextFrame <= 0) {
                rect.left += rect.width;
                if (rect.left >= spr.value().sizeX)
                    rect.left = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate to the left
            if (spr.value().sheetDirection == 2 && spr.value().nextFrame <= 0) {
                rect.left -= rect.width;
                if (rect.left < 0)
                    rect.left = spr.value().sizeX;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate downward
            if (spr.value().sheetDirection == 3 && spr.value().nextFrame <= 0) {
                rect.top += rect.height;
                if (rect.top >= spr.value().sizeY)
                    rect.top = 0;
                spr.value().nextFrame = spr.value().frameTime;
            }
            // Animate upward
            if (spr.value().sheetDirection == 4 && spr.value().nextFrame <= 0) {
                rect.top -= rect.height;
                if (rect.top < 0)
                    rect.top = spr.value().sizeY;
                spr.value().nextFrame = spr.value().frameTime;
            }
            spr.value().sprite.setTextureRect(rect);
        }
    }
}

void rtp::ClientSystems::drawSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &sprites = r.getComponents<Drawable>();

    // Draw & update sheets
    for (int i = 0; i < positions.size() && i < sprites.size(); i++) {
        auto &pos = positions[i];
        auto &spr = sprites[i];

        if (pos.has_value() && spr.has_value()) {
            spr.value().sprite.setPosition({pos.value().x, pos.value().y});
            _w.draw(spr.value().sprite);
        }
    }
}

void rtp::ClientSystems::writeSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &writables = r.getComponents<Writable>();

    for (int i = 0; i < positions.size() && i < writables.size(); i++) {
        auto &pos = positions[i];
        auto &wrt = writables[i];

        if (pos.has_value() && wrt.has_value()) {
            wrt.value()._txt.setPosition({pos.value().x, pos.value().y});
            _w.draw(wrt.value()._txt);
        }
    }
}

void rtp::ClientSystems::controlFireSystem(eng::Registry &r)
{
    auto &shooters = r.getComponents<Shooter>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < shooters.size(); i++) {
        auto &sht = shooters[i];
        auto &ctrl = controllables[i];

        if (sht.has_value() && ctrl.has_value()) {
            if (sht.value().nextFire > 0) {
                sht.value().nextFire -= _delta.asSeconds();
                ctrl.value().chat = false;
            }
            if (ctrl.value().shoot && sht.value().nextFire <= 0)  {
                sht.value().shoot = true;
                ctrl.value().chat = true;
                sht.value().nextFire = sht.value().fireRate / 1;
            }
        }
    }
}

void rtp::ClientSystems::backgroundSystem(eng::Registry &r)
{
    auto &bgs = r.getComponents<Background>();
    auto &poss = r.getComponents<Position>();

    for (int i = 0; i < bgs.size() && i < poss.size(); i++) {
        auto &pos = poss[i];
        auto &bg = bgs[i];

        if (pos.has_value() && bg.has_value()) {
            if (pos.value().x <= -1920)
                pos.value().x = 1920;
            bg.value().sprite.setPosition({pos.value().x, pos.value().y});
            _w.draw(bg.value().sprite);
        }
    }
}

void rtp::ClientSystems::shootSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &shooters = r.getComponents<Shooter>();

    for (int i = 0; i < positions.size() && i < shooters.size(); i++) {
        auto &pos = positions[i];
        auto &sht = shooters[i];
        
        if (pos.has_value() && sht.has_value()) {
            if (sht.value().shoot) {
                float x = pos.value().x + sht.value().shootPoint[0];
                float y = pos.value().y + sht.value().shootPoint[1];
                float z = pos.value().z;
                sht.value().shoot = false;
                eng::Entity bullet = r.spawnEntity();
                r.addComponent(bullet, rtp::Velocity(15, 0));
                r.addComponent(bullet, rtp::Position(x, y, z));
                r.addComponent(bullet, rtp::Drawable(sht.value().bulletSpritePath));
                r.addComponent(bullet, rtp::AudioSource("assets/fire.wav", true));
                r.addComponent(bullet, rtp::Bullet(2));
            }
        }
    }
}

void rtp::ClientSystems::playSoundSystem(eng::Registry &r)
{
    auto &sounds = r.getComponents<AudioSource>();

    for (int i = 0; i < sounds.size(); i++) {
        auto &snd = sounds[i];

        if (snd.has_value()) {
            if (snd.value().toPlay) {
                snd.value().toPlay = false;
                snd.value().sound.play();
            }
        }
    }
}

void rtp::ClientSystems::positionSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<Position>();
    auto &velocities = r.getComponents<Velocity>();

    for (int i = 0; i < positions.size() && i < velocities.size(); i++) {
        auto &pos = positions[i];
        auto &vel = velocities[i];

        if (pos.has_value() && vel.has_value()) {
            pos.value().x += (vel.value().x * _delta.asSeconds() * 20);
            pos.value().y += (vel.value().y * _delta.asSeconds() * 20);
        }
    }
}

void rtp::ClientSystems::sendData(eng::Registry &r)
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

void rtp::ClientSystems::killDeadEnemies(eng::Registry &r)
{
    auto &ennemies = r.getComponents<EnemyStats>();

    for (int i = 0; i < ennemies.size(); i++)
        if (ennemies[i].has_value())
            if (ennemies[i].value().health <= 0)
                r.killEntity(eng::Entity(i));
}

void rtp::ClientSystems::receiveData(eng::Registry &r)
{
    int e = 0;
    bool toBuild = false;

    while (true) {
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
            writeInChatBox(r, "A new entity has been added by the server!", ChatBoxStyle::EVENT);
        }
        if (_dataBuffer[0].COMPONENT_NAME == POSITION)
            r.emplaceComponent<Position>(eng::Entity(e), Position(data.valueA, data.valueB, data.valueC));
        if (_dataBuffer[0].COMPONENT_NAME == VELOCITY)
            r.emplaceComponent<Velocity>(eng::Entity(e), Velocity(data.valueA, data.valueB));
        if (data.COMPONENT_NAME == ENEMY_STATS) {
            r.emplaceComponent<EnemyStats>(eng::Entity(e), EnemyStats(data.valueB, data.valueA));
            if (toBuild)
                _completeEnemy(r, e);
        }
        if (data.COMPONENT_NAME == PLAYER_STATS) {
            r.emplaceComponent<PlayerStats>(eng::Entity(e), PlayerStats(data.valueA, 10, data.valueB, data.valueC));
            if (toBuild)
                _completePlayer(r, e);
        }

    }
}

int rtp::ClientSystems::_getSyncedEntity(eng::Registry &r, int syncId)
{
    auto synceds = r.getComponents<Synced>();

    for (int i = 0; i < synceds.size(); i++) {
        if (synceds[i].has_value()) {
            if (synceds[i].value().id == syncId) {
                return (i);
            }
        }
    }
    return (-1);
}

// Bullets are considered as (x, y) points
void rtp::ClientSystems::playerBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<Position>();

    for (int i = 0; i < blts.size() && i < poss.size(); i++) {
        if (blts[i].has_value() && poss[i].has_value()) {
            _bulletAgainstEnemy(r, eng::Entity(i));
        }
    }
}

void rtp::ClientSystems::_bulletAgainstEnemy(eng::Registry &r, eng::Entity blt)
{
    auto &enms = r.getComponents<EnemyStats>();
    auto &poss = r.getComponents<Position>();
    auto &rcts = r.getComponents<RectCollider>();
    auto &p = r.getComponents<Position>()[blt.getId()].value();
    auto &b = r.getComponents<Bullet>()[blt.getId()].value();

    for (int i = 0; i < enms.size() && i < poss.size() && i < rcts.size(); i++) {
        if (enms[i].has_value() && poss[i].has_value() && rcts[i].has_value()) {
            auto &enm = enms[i].value();
            auto &pos = poss[i].value();
            auto &rct = rcts[i].value();
            if (p.x >= pos.x && p.y >= pos.y) {
                if (p.x <= pos.x + rct.width && p.y <= pos.y + rct.height) {
                    enm.health -= b.damage;
                    r.killEntity(blt);
                }
            }
        }
    }
}

bool rtp::ClientSystems::windowOpen()
{
    return this->_w.isOpen();
}

void rtp::ClientSystems::eventCloseWindow()
{
    while (this->_w.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_w.close();
    }
}

void rtp::ClientSystems::updDeltaTime()
{
    _delta = _c.restart();
}

// Just a test, need to be really implemented
void rtp::ClientSystems::controlChatSystem(eng::Registry &r)
{
    auto &controllables = r.getComponents<Controllable>();
    auto &writables = r.getComponents<Writable>();

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            if (ctrl.value().chat) {
                std::stringstream ss;
                ss << "Chat " << ctrl.value().count;
                writeInChatBox(r, ss.str(), ChatBoxStyle::CHAT);
                ctrl.value().count++;
                ctrl.value().chat = false;
            }
            if (ctrl.value().event) {
                writeInChatBox(r, "Event", ChatBoxStyle::EVENT);
                ctrl.value().event = false;
            }
        }
    }
}

void rtp::ClientSystems::setText(eng::Registry &r, std::string message, std::optional<rtp::Writable> &wrt,  rtp::ClientSystems::ChatBoxStyle style)
{
    if (wrt.has_value()) {
        wrt.value()._txt.setStyle(sf::Text::Bold);
        wrt.value()._txt.setString(message);
    }
}

void rtp::ClientSystems::setText(eng::Registry &r, std::string message, std::string name,  rtp::ClientSystems::ChatBoxStyle style)
{
    auto &writables = r.getComponents<Writable>();

    for (int i = 0; i < writables.size(); i++) {
        auto &wrt = writables[i];
        if (wrt.has_value() && wrt.value()._name == name) {
            wrt.value()._txt.setString(message);
            if (style == ClientSystems::CHAT) {
                wrt.value()._txt.setStyle(sf::Text::Regular);
                wrt.value()._txt.setFillColor(sf::Color::White);
            }
            if (style == ClientSystems::EVENT) {
                wrt.value()._txt.setStyle(sf::Text::Italic);
                wrt.value()._txt.setFillColor(sf::Color::Blue);
            }
        }
    }
}

void rtp::ClientSystems::writeInChatBox(eng::Registry &r, std::string message, rtp::ClientSystems::ChatBoxStyle style)
{
    auto &writables = r.getComponents<Writable>();
    auto &positions = r.getComponents<Position>();

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

void rtp::ClientSystems::addChatBox(eng::Registry &reg)
{
    eng::Entity chatBox = reg.spawnEntity();

    reg.addComponent<rtp::Writable>(chatBox, rtp::Writable("ChatBox1"));
    reg.addComponent<rtp::Position>(chatBox, rtp::Position(0, 980, 0));
}

void rtp::ClientSystems::_completeEnemy(eng::Registry &r, int e)
{
    int type = r.getComponents<EnemyStats>()[e].value().enemyType;
    if (type == 0)
        r.emplaceComponent<Drawable>(eng::Entity(e), Drawable("assets/flyers.png", 3, sf::IntRect(0, 0, 40, 16), 0.005));
        r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40, 16));
}

void rtp::ClientSystems::_completePlayer(eng::Registry &r, int e)
{
    int playerId = r.getComponents<PlayerStats>()[e].value().playerId;
    sf::IntRect rect = {0, 0, 65, 49};
    r.addComponent<rtp::Shooter>(eng::Entity(e), rtp::Shooter("assets/bullet.png", 25, 4, {65, 25}));
    r.emplaceComponent<RectCollider>(eng::Entity(e), RectCollider(40, 16));
    if (playerId == 2)
        rect.top = 49;
    if (playerId == 3)
        rect.top = 98;
    if (playerId == 4)
        rect.top = 147;
    r.addComponent<rtp::Drawable>(eng::Entity(e), rtp::Drawable("assets/players.png", 1, rect, 0.10));
}