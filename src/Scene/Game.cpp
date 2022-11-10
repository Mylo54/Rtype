// /*
// ** EPITECH PROJECT, 2022
// ** rtype
// ** File description:
// ** Game
// */

// #include "Game.hpp"

// rtp::Game::Game(rtp::scene_package_t &pack, eng::RegistryManager &manager):
//                 AScene(pack), _manager(manager)
// {
//     _manager.addRegistry("R2");
//     setupRegistry();
//     _addBackgrounds(_manager.getTop());
//     _addScore(_manager.getTop());
//     _addMusic(_manager.getTop(), "assets/music.ogg");
// }

// rtp::Game::~Game()
// {
// }

// void rtp::Game::_addMusic(eng::Registry &reg, std::string filepath)
// {
//     eng::Entity music = reg.spawnEntity();

//     reg.addComponent<eng::Music>(music, eng::Music(filepath, true));
// }

// eng::Entity rtp::Game::addPlayer(eng::Registry &reg, int playerId, int syncId)
// {
//     eng::Entity player = reg.spawnEntity();

//     reg.addComponent<eng::Position>(player, eng::Position(200, 540, 0));
//     reg.addComponent<eng::Velocity>(player, eng::Velocity());
//     // reg.addComponent<rtp::Shooter>(player, rtp::Shooter("assets/bullet.png", 25, 4, {60, 25}));
//     sf::IntRect rect = {0, ((playerId - 1) * 49), 60, 49};
//     reg.addComponent<eng::Drawable>(player, eng::Drawable(_texture.getTextureFromFile("assets/players.png"), 1, rect, 0.10));
//     // reg.addComponent<rtp::Controllable>(player, rtp::Controllable());
//     // reg.addComponent<rtp::Synced>(player, rtp::Synced(syncId));
//     // reg.addComponent<rtp::PlayerStats>(player, rtp::PlayerStats(playerId));
//     reg.addComponent<eng::RectCollider>(player, eng::RectCollider(40, 16));
//     reg.addComponent<eng::RigidBody>(player, eng::RigidBody(eng::RigidBody::RECTANGLE, false, 1.0f));
//     auto &smoke = reg.addComponent<eng::ParticleEmitter>(player, eng::ParticleEmitter())[player.getId()].value();

//     smoke.setParticleTexture(eng::PARTICLE_TYPE::Sprite, "assets/smokeParticle.png");
//     smoke.setBaseSpeed(500, 1000);
//     smoke.setLifetime(5);
//     smoke.setBaseRotation(260, 280);
//     smoke.setEmittingRate(0.01);
//     smoke.setMaxNumber(100);
//     smoke.isLocal = false;
//     smoke.setParticleColorRandom(true);

//     std::cout << "You are player " << playerId << std::endl;
//     return player;
// }

// eng::Entity rtp::Game::_addEnemy(eng::Registry &reg)
// {
//     eng::Entity enemy = reg.spawnEntity();
//     float scale = (rand() % 10) + 1;

//     reg.addComponent<eng::Position>(enemy, eng::Position(1920 + (rand() % 2000), rand() % 1080, 0));
//     reg.addComponent<eng::Velocity>(enemy, eng::Velocity(-100, 0));
//     reg.addComponent<eng::Drawable>(enemy, eng::Drawable(_texture.getTextureFromFile("assets/flyers.png"), 3, sf::IntRect(0, 0, 40, 16), 0.10));
//     // reg.addComponent<rtp::EnemyStats>(enemy, rtp::EnemyStats(5));
//     reg.addComponent<eng::RectCollider>(enemy, eng::RectCollider(40*scale, 16*scale));

//     reg.getComponents<eng::Drawable>()[enemy.getId()].value().sprite.setScale(scale, scale);
//     return enemy;
// }

// void rtp::Game::_addScore(eng::Registry &reg)
// {
//     eng::Entity score = reg.spawnEntity();

//     reg.addComponent<eng::Position>(score, eng::Position(850, 0, 0));
//     reg.addComponent<eng::Writable>(score, eng::Writable("score", "SCORE:000 000", "assets/MetroidPrimeHunters.ttf"));
// }

// void rtp::Game::_addBackgrounds(eng::Registry &reg)
// {
//     for (int i = 0; i < 6; i++) {
//         eng::Entity bg = reg.spawnEntity();
//         reg.addComponent<eng::Position>(bg, eng::Position((i % 2) * 1920, 0, 0));
//         if (i < 2) {
//             reg.addComponent<eng::Velocity>(bg, eng::Velocity(-400, 0));
//             reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/foreground.png")));
//             // reg.addComponent<rtp::Background>(bg, rtp::Background());
//         } else if (i < 4) {
//             reg.addComponent<eng::Velocity>(bg, eng::Velocity(-200, 0));
//             reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/middleground.png")));
//             // reg.addComponent<rtp::Background>(bg, rtp::Background());
//         } else {
//             reg.addComponent<eng::Velocity>(bg, eng::Velocity(-100, 0));
//             reg.addComponent<eng::Drawable>(bg, eng::Drawable(_texture.getTextureFromFile("assets/background.png")));
//             // reg.addComponent<rtp::Background>(bg, rtp::Background());
//         }
//     }
// }