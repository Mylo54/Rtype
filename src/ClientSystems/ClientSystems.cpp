/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystems
*/

#include "ClientSystems.hpp"

rtp::ClientSystems::ClientSystems(eng::GraphicSystems &gfx, std::string adress, int port,
boost::asio::ip::udp::socket &socket, eng::SuperInput &inputs,
eng::TextureManager &textureManager):
_w(gfx.getRenderWindow()), _c(gfx.getClock()), _delta(gfx.getDelta()),
_isWindowFocused(gfx.isWindowFocused()), _gfx(gfx), _inputs(inputs), _textureManager(textureManager)
{
    _isButtonRelease = false;
    _isEscapeRelease = false;
}

rtp::ClientSystems::~ClientSystems()
{
}

void rtp::ClientSystems::controlMovementSystem(eng::Registry &r)
{
    auto &velocities = r.getComponents<eng::Velocity>();
    auto &controllables = r.getComponents<Controllable>();

    for (int i = 0; i < controllables.size() && i < velocities.size(); i++) {
        auto &ctrl = controllables[i];
        auto &vel = velocities[i];

        if (vel.has_value() && ctrl.has_value()) {
            // Left & Right
            vel.value().x += ctrl.value().xAxis * _delta.asSeconds() * 20 * 2;

            // Up & Down
            vel.value().y += ctrl.value().yAxis * _delta.asSeconds() * 20 * 2;
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

void rtp::ClientSystems::backgroundSystem(eng::Registry &r)
{
    auto &bgs = r.getComponents<Background>();
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < bgs.size() && i < poss.size(); i++) {
        if (poss[i].has_value() && bgs[i].has_value()) {
            auto &pos = poss[i].value();
            auto &bg = bgs[i].value();
            if (pos.x <= -1920)
                pos.x = 1920;
        }
    }
}

void rtp::ClientSystems::controlSystem(eng::Registry &r, eng::RegistryManager &manager)
{
    if (_isWindowFocused == false) {
        return;
    }
    auto &controllables = r.getComponents<Controllable>();
    bool press = true;

    for (int i = 0; i < controllables.size(); i++) {
        auto &ctrl = controllables[i];

        if (ctrl.has_value()) {
            // Move analog & button (round to integer because )
            ctrl.value().xAxis = _inputs.getActionStrength("Move x") > 0.1f ? 1.0f : 0.0f;
            ctrl.value().xAxis = _inputs.getActionStrength("Move x") < -0.1f ? -1.0f : ctrl.value().xAxis;
            ctrl.value().yAxis = _inputs.getActionStrength("Move y")> 0.1f ? 1.0f : 0.0f;
            ctrl.value().yAxis = _inputs.getActionStrength("Move y") < -0.1f ? -1.0f : ctrl.value().yAxis;

            // Move -button
            ctrl.value().xAxis -= _inputs.getActionStrength("Move -x");
            ctrl.value().yAxis -= _inputs.getActionStrength("Move -y");
            // Shoot
            ctrl.value().shoot = _inputs.isActionPressed("Fire");

            // Pause menu (move this somewhere else, please)
            if (_inputs.isActionJustReleased("Pause")) {
                std::cout << "[DEBUG] key escape pressed" << std::endl;
                rtp::PauseMenu *pm = new PauseMenu(manager, _gfx, _textureManager);
                std::cout << "[DEBUG] crea pause menu" << std::endl;
            }
        }
    }
}

void rtp::ClientSystems::buttonStateSystem(eng::Registry &r)
{
    auto &buttons = r.getComponents<Button>();
    auto &positions = r.getComponents<eng::Position>();
    auto &sprite = r.getComponents<eng::Drawable>();
    auto mousePos = _inputs.getMousePosition();

    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].has_value()) {
            auto &btn = buttons[i].value();
            auto &spr = sprite[i].value();
            auto &pos = positions[i].value();
            sf::IntRect rect = spr.sprite.getTextureRect();

            if (mousePos[0] > pos.x && mousePos[0] < pos.x + btn.width
            && mousePos[1] > pos.y && mousePos[1] < pos.y + btn.height) {
                rect.left = (spr.sheetDirection == 1) ? rect.width : 0;
                rect.top = (spr.sheetDirection == 3) ? rect.height : 0;
                if (_inputs.isActionPressed("MouseLeft")) {
                    std::cout << "debug" << std::endl;
                    rect.left += (spr.sheetDirection == 1) ? rect.width : 0;
                    rect.top += (spr.sheetDirection == 3) ? rect.height : 0;
                }
            } else {
                rect.left = (spr.sheetDirection == 1) ? 0 : rect.width;
                rect.top = (spr.sheetDirection == 3) ? 0 : rect.height;
            }
            spr.sprite.setTextureRect(rect);
        }
    }
}


void rtp::ClientSystems::shootSystem(eng::Registry &r)
{
    auto &positions = r.getComponents<eng::Position>();
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
                r.addComponent(bullet, eng::Velocity(300, 0));
                r.addComponent(bullet, eng::Position(x, y, z));
                r.addComponent(bullet, eng::Drawable(sht.value().bulletSpritePath));
                r.addComponent(bullet, eng::Sound("assets/fire.wav", true));
                r.addComponent(bullet, rtp::Bullet(2));
            }
        }
    }
}

// Max speed should be defined elsewhere...
void rtp::ClientSystems::limitPlayer(eng::Registry &r)
{
    auto &pos = r.getComponents<eng::Position>();
    auto &ves = r.getComponents<eng::Velocity>();
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
    auto &poss = r.getComponents<eng::Position>();

    for (int i = 0; i < blts.size() && i < poss.size(); i++) {
        if (blts[i].has_value() && poss[i].has_value()) {
            _bulletAgainstEnemy(r, eng::Entity(i));
        }
    }
}

void rtp::ClientSystems::_bulletAgainstEnemy(eng::Registry &r, eng::Entity blt)
{
    auto &enms = r.getComponents<EnemyStats>();
    auto &poss = r.getComponents<eng::Position>();
    auto &rcts = r.getComponents<eng::RectCollider>();
    auto &p = r.getComponents<eng::Position>()[blt.getId()].value();
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
    auto &writables = r.getComponents<eng::Writable>();

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

void rtp::ClientSystems::setText(eng::Registry &r, std::string message, std::optional<eng::Writable> &wrt,  rtp::ClientSystems::ChatBoxStyle style)
{
    if (wrt.has_value()) {
        wrt.value()._txt.setStyle(sf::Text::Bold);
        wrt.value()._txt.setString(message);
    }
}

void rtp::ClientSystems::setText(eng::Registry &r, std::string message, std::string name,  rtp::ClientSystems::ChatBoxStyle style)
{
    auto &writables = r.getComponents<eng::Writable>();

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

void rtp::ClientSystems::addChatBox(eng::Registry &reg)
{
    eng::Entity chatBox = reg.spawnEntity();

    reg.addComponent<eng::Writable>(chatBox, eng::Writable("ChatBox1"));
    reg.addComponent<eng::Position>(chatBox, eng::Position(0, 980, 0));
}

void rtp::ClientSystems::buttonSystem(eng::Registry &r, eng::RegistryManager &manager)
{
    auto &buttons = r.getComponents<Button>();
    auto &positions = r.getComponents<eng::Position>();
    auto mousePos = _inputs.getMousePosition();

    if (_inputs.isActionJustReleased("MouseLeft")) {
        for (int i = 0; i < buttons.size() && i < positions.size(); i++) {
            if (buttons[i].has_value() && positions[i].has_value()) {
                auto &btn = buttons[i].value();
                auto &pos = positions[i].value();

                if (mousePos[0] > pos.x && mousePos[0] < pos.x + btn.width
                && mousePos[1] > pos.y && mousePos[1] < pos.y + btn.height) {
                    btn.btnFunction(manager);
                }
            }
        }
        return;
    }
}

void rtp::ClientSystems::killBullets(eng::Registry &r)
{
    auto &blts = r.getComponents<Bullet>();
    auto &poss = r.getComponents<eng::Position>();

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

void rtp::ClientSystems::killOutOfBounds(eng::Registry &r)
{
    auto &poss = r.getComponents<eng::Position>();
    auto &drawables = r.getComponents<eng::Drawable>();

    for (int i = 0; i < poss.size() && i < drawables.size(); i++) {
        if (poss[i].has_value() && drawables[i].has_value()) {
            auto pos = poss[i].value();
            auto drw = drawables[i].value();
            if (!drw.protect) {
                if (pos.x > 1920 || pos.x < (-1 * drw.sizeX))
                    r.killEntity(eng::Entity(i));
                else if (pos.y > 1080 || pos.y < (-1 * drw.sizeY))
                    r.killEntity(eng::Entity(i));
            }
        }
    }
}