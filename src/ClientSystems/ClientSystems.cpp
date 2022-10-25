/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystems
*/

#include "ClientSystems.hpp"

rtp::ClientSystems::ClientSystems(sf::RenderWindow &w, sf::Clock &c,
sf::Time &delta, std::string adress, int port,
boost::asio::ip::udp::socket &socket) : _w(w), _c(c), _delta(delta)
{
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

void rtp::ClientSystems::controlMovementSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * _delta.asSeconds() * 20 * 2;
            vel.value().x += (vel.value().x > 0) ? -_delta.asSeconds() * 20 : 0;
            vel.value().x += (vel.value().x < 0) ? _delta.asSeconds() * 20 : 0;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * _delta.asSeconds() * 20 * 2;
            vel.value().y += (vel.value().y > 0) ? -_delta.asSeconds() * 20 : 0;
            vel.value().y += (vel.value().y < 0) ? _delta.asSeconds() * 20 : 0;
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
                sht.value().nextFire = sht.value().fireRate / 1;
            }
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

// Max speed should be defined elsewhere...
void rtp::ClientSystems::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<Position>();
    auto &ves = r.getComponents<Velocity>();
    auto &pls = r.getComponents<PlayerStats>();
    float maxSpeed = 15;

    for (int i = 0; i < pos.size() && i < ves.size() && i < pls.size(); i++) {
        if (pos[i].has_value() && ves[i].has_value() && pls[i].has_value()) {
            auto &position = pos[i].value();
            auto &velocity = ves[i].value();
            auto &playerSt = pls[i].value();

            position.x = (position.x >= 1860) ? 1860 : position.x;
            position.x = (position.x < 0) ? 0 : position.x;
            position.y = (position.y >= 982) ? 982 : position.y;
            position.y = (position.y < 0) ? 0 : position.y;

            velocity.x = (velocity.x >= maxSpeed) ? maxSpeed : velocity.x;
            velocity.x = (velocity.x <= -maxSpeed) ? -maxSpeed : velocity.x;
            velocity.y = (velocity.y >= maxSpeed) ? maxSpeed : velocity.y;
            velocity.y = (velocity.y <= -maxSpeed) ? -maxSpeed : velocity.y;
        }
    }
}



void rtp::ClientSystems::killDeadEnemies(eng::Registry &r)
{
    auto &ennemies = r.getComponents<EnemyStats>();

    for (int i = 0; i < ennemies.size(); i++) {
        if (ennemies[i].has_value()) {
            if (ennemies[i].value().health <= 0) {
                r.killEntity(eng::Entity(i));
                _score += 10;
                std::stringstream s;
                s << "score:";
                s << ((_score / 100 > 10) ? "0" : "00") <<  _score / 100 << " ";
                s << ((_score % 100 > 10) ? "0" : "00") << _score % 100;
                setText(r, s.str(), "score", CHAT);
            }
        }

    }
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

void rtp::ClientSystems::buttonSystem(eng::Registry &r)
{
    auto &buttons = r.getComponents<Button>();
    auto &positions = r.getComponents<Position>();
    auto mousePos = sf::Mouse::getPosition(_w);

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
        return;
    for (int i = 0; i < buttons.size() && i < positions.size(); i++) {
        if (buttons[i].has_value() && positions[i].has_value()) {
            auto &btn = buttons[i].value();
            auto &pos = positions[i].value();
            
            if (mousePos.x > pos.x && mousePos.x < pos.x + btn.width
            && mousePos.y > pos.y && mousePos.y < pos.y + btn.height) {
                btn.btnFunction();
            }
        }
    }
}

void rtp::ClientSystems::killBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<Position>();

    for (int i = 0; i < blts.size(); i++) {
        if (blts[i].has_value()) {
            auto blt = blts[i].value();
            auto pos = poss[i].value();

            if (pos.x > 1920 || pos.x < -1)
                r.killEntity(eng::Entity(i));
            else if (pos.y > 1080 || pos.y < -1)
                r.killEntity(eng::Entity(i));
        }
    }
}

void rtp::ClientSystems::playMusicSystem(eng::Registry &r)
{
    auto &sounds = r.getComponents<Music>();

    for (int i = 0; i < sounds.size(); i++) {
        auto &snd = sounds[i];

        if (snd.has_value()) {
            if (snd.value().toPlay) {
                snd.value().toPlay = false;
                snd.value().music->play();
            }
        }
    }
}

void rtp::ClientSystems::killOutOfBounds(eng::Registry &r)
{
    auto &poss = r.getComponents<Position>();
    auto &drawables = r.getComponents<Drawable>();

    for (int i = 0; i < poss.size() && i < drawables.size(); i++) {
        if (poss[i].has_value() && drawables[i].has_value()) {
            auto pos = poss[i].value();
            auto drw = drawables[i].value();
            if (pos.x > 1920 || pos.x < (-1 * drw.sizeX))
                r.killEntity(eng::Entity(i));
            else if (pos.y > 1080 || pos.y < (-1 * drw.sizeY))
                r.killEntity(eng::Entity(i));
        }
    }
}