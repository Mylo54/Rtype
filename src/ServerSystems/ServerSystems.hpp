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
#include "../Engine/Registry.hpp"
#include "../Components/Components.hpp"
#include <mutex>
#include <vector>
#include <thread>
#include <condition_variable>
#include <boost/container/vector.hpp>
#include <ctime>
#include <chrono>

namespace rtp {
    class ServerSystems {
        public:
            ServerSystems(boost::asio::ip::udp::socket &socket,
            std::mutex &mutex, std::vector<rtp::inputPayload_t> &listDataRec,
            std::vector<boost::asio::ip::udp::endpoint> &endpoints);
            ~ServerSystems();

            /// @brief Add a client endpoint
            /// @param address The IPv4 address of the receiver
            /// @param port The port of the receiver
            void addEndpoint(std::string address, int port);

            /// @brief Remove a client endpoint
            /// @param address The IPv4 address of the receiver
            /// @param port The port of the receiver
            void removeEndPoint(std::string address, int port);
            
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

            /// @brief A generic funciton that send a boost::array to all stored endpoints
            /// @param data_tbs The data to be sent to all clients
            void sendSyncedDataToAll(boost::array<server_payload_t, 1> dataTbs);
            
            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);

            void updDeltaTime();
            /// @brief Limit the framerate if needed
            void limitTime();

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
            void spawnEnemies(eng::Registry &r);
        protected:
        protected:
        private:
            /// @brief A method that gets a synced entity id
            /// @param syncId The synced component id
            /// @return The entity id
            int _getSyncedEntity(eng::Registry &r, int syncId);

            /// @brief A method for sending a package to every endpoint
            /// @todo find how to contain the data that we need to send to the client
            void _sendSubsystem();

            /// @brief edit the serverpayload struct passed as argument
            /// @param pl the serverpayload struct
            /// @param componentName the component type enum
            /// @param values the values in order (valueA, valueB, valueC) no more than 3
            /// @param syncId the synchronization ID
            /// @param shot if shot event (false by default)
            void _editDataTbs(rtp::server_payload_t &pl, int componentName, std::vector<float> values, int syncId, bool shot);

            /// @brief A short system which damage an enemy and destroys bullets
            /// @param r The Registry on which to apply the system
            /// @param b The bullets data
            /// @param p The Position of the bullet
            void _bulletAgainstEnemy(eng::Registry &r, eng::Entity blt);

            /// @brief Get the delta time as seconds
            /// @return the delta time as seconds
            float _getDeltaAsSeconds();

            /// @brief The time to wait between each enemy spawn
            float _enemyRate;

            /// @brief The timer until the next enemy spawns
            float _enemyTimer;

            /// @brief data sending socket
            boost::asio::ip::udp::socket &_socket;
            /// @brief list (vector) of client endpoints
            std::vector<boost::asio::ip::udp::endpoint> &_endpoints;
            /// @brief atomic variable of acces to listDataRec
            std::mutex &_mutex;
            /// @brief List of all received payload
            std::vector<inputPayload_t> &_listDataRec;

            /// @brief The delta time since last frame in microseconds
            long _delta = 0;
            /// @brief Elapsed time since
            float _elapsedTime = 0;
            /// @brief Tick per seconds of the server
            float _tps = 60;
            /// @brief Saved value to update the delta time
            std::chrono::steady_clock::time_point _lastUpdate;
    };
};

#endif /* !SERVERSYSTEMS_HPP_ */
