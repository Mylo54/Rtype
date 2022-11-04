/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystems
*/

#ifndef SERVERSYSTEMS_HPP_
#define SERVERSYSTEMS_HPP_

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../NetworkStructs.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Components/Components.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>
#include <boost/container/vector.hpp>
#include <ctime>
#include <chrono>

namespace rtp {
    /// @brief A class holding every server systems
    class ServerSystems {
        public:
            /// @brief ServerSystems object constructeur
            /// @param socket udp socket of the server
            /// @param mutex 
            /// @param listDataRec 
            /// @param endpoints 
            ServerSystems(boost::asio::ip::udp::socket &socket,
            std::mutex &mutex, std::vector<std::vector<int>> &listDataRec,
            std::vector<boost::asio::ip::udp::endpoint> &endpoints);
            ~ServerSystems();
            
            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system 
            void positionSystem(eng::Registry &r);

            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

            /// @brief A system which damage enemies colliding a player's bullet
            /// @param r The Registry on which to apply the system
            void playerBullets(eng::Registry &r);

            /// @brief A system which kill dead enemies
            /// @param r The Registry on which to apply the system
            void killDeadEnemies(eng::Registry &r);

            /// @brief A system which sends data to ALL clients
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);

            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);

            void updDeltaTime();
            void limitTime();

            /// @brief limits the server speed to the previously set "tickrate"
            void limitTickRate();

            /// @brief Prevents player from going out of the window and limit its velocity
            /// @param reg The registry on which to apply the system
            void limitPlayer(eng::Registry &r);

            /// @brief Kill entities that are offscreen
            /// @param r The registry on which to apply the system
            void killOutOfBounds(eng::Registry &r);

            /// @brief Set the enemy spawn rate
            /// @param seconds Each 'seconds' time we spawn a new enemy
            void setEnemyRate(float seconds);

            /// @brief A system which spawns enemies periodicaly
            /// (Set the spawnRate with setEnemyRate(float))
            /// @param r The Registry on which to apply the system
            /// @param level The level
            void spawnEnemies(eng::Registry &r, int level);

            /// @brief Set the bonus spawn rate
            /// @param seconds Each 'seconds' time we spawn a new bonus
            void setBonusRate(float seconds);

            /// @brief A system which spawns bonuses periodicaly
            /// (Set the spawnRate with setBonusRate(float))
            /// @param r The Registry on which to apply the system
            /// @param x The horizontal origin position of the bonus
            /// @param y The vertical origin position of the bonus
            void spawnBonus(eng::Registry &r, float x, float y);

            /// @brief A system managing collisions
            /// @param r The Registry on which to apply the system
            void collisions(eng::Registry &r);
            /// @brief A system managing collisions between bonuses and a specific client
            /// @param r The Registry on which to apply the system
            /// @param entity The entity on which to check collision with bonus
            void bonusCollision(eng::Registry &r, int entity);
            /// @brief A system managing collisions between bonuses and a specific client
            /// @param r The Registry on which to apply the system
            /// @param entity The entity on which to check collision with enemy
            void enemyCollision(eng::Registry &r, int entity);
            /// @brief A system managing collisions between clients
            /// @param r The Registry on which to apply the system
            void playerCollision(eng::Registry &r);
            /// @brief A system checking if 2 entities are colliding
            /// @param pos1 Position of the first entity
            /// @param rect1 RectCollider of the first entity
            /// @param pos2 Position of the second entity
            /// @param rect2 RectCollider of the second entity
            /// @return true if colliding, else otherwise
            bool isColliding(eng::Position &pos1, eng::RectCollider & rect1, eng::Position &pos2, eng::RectCollider & rect2);
            /// @brief A system managing the collecting of bonus by a player
            /// @param r The Registry on which to apply the system
            /// @param player The player entity ID
            /// @param bonus The bonus entity ID
            void collectBonus(eng::Registry &r, int player, int bonus);

            /// @brief Get the delta time in second since last tick
            /// @return a reference to the delta time
            float &getDelta();

            /// @brief Sets the tick rate for the server
            /// @param tps number of ticks per second
            void setTickRate(unsigned int tps);
        protected:
        private:
            /// @brief A method that gets a synced entity id
            /// @param syncId The synced component id
            /// @return The entity id
            int _getSyncedEntity(eng::Registry &r, int syncId);

            /// @brief A generic function that send a vector to all endpoints
            /// @param vector The vector to send to all endpoints
            void _sendDataToAll(std::vector<int> &vector);

            /// @brief adds ints to the payload in parameters
            /// @param payload ref to the payload vector
            /// @param toAdd the ints to add to the payload
            void _addToPayload(std::vector<int> &payload, std::vector<int> toAdd);

            /// @brief A short system which damage an enemy and destroys bullets
            /// @param r The Registry on which to apply the system
            /// @param b The bullets data
            /// @param p The Position of the bullet
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);

            /// @brief The time to wait between each enemy spawn
            float _enemyRate;

            /// @brief The timer until the next enemy spawns
            float _enemyTimer;

            /// @brief The time to wait between each bonus spawn
            float _bonusRate;

            /// @brief The timer until the next bonus spawns
            float _bonusTimer;

            /// @brief data sending socket
            boost::asio::ip::udp::socket &_socket;
            /// @brief list (vector) of client endpoints
            std::vector<boost::asio::ip::udp::endpoint> &_endpoints;
            /// @brief atomic variable of acces to listDataRec
            std::mutex &_mutex;
            /// @brief List of all received payload
            std::vector<std::vector<int>> &_listDataRec;

            /// @brief The delta time since last frame in microseconds
            float _delta = 0;

            std::clock_t _lastClockTime = std::clock();

            /// @brief Tick per seconds of the server
            float _tps = 0;

            /// @brief Saved value to update the delta time
            std::chrono::steady_clock::time_point _lastUpdate;
    };
};

#endif /* !SERVERSYSTEMS_HPP_ */
