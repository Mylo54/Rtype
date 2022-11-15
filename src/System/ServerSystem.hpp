/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ServerSystem
*/

#ifndef SERVERSYSTEM_HPP_
#define SERVERSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Network/UDPServer.hpp"
#include <thread>
#include <chrono>

namespace rtp
{
    enum syncedComponent{
        position,
        velocity,
        playerStats,
        enemyStats
    };
    class ServerSystem {
        public:
            ServerSystem(rtp::UDPServer &server);
            ~ServerSystem();

            void sendData(eng::Registry &r);
            void receiveData(eng::Registry &, std::vector<int> data,
            std::mutex &dataMutex);
            void limitTickRate();
            void setTickRate(unsigned int tps);
            float &getDelta();
        protected:
        private:
            /// @brief The delta time since last frame in microseconds
            float _delta = 0;

            std::clock_t _lastClockTime = std::clock();

            /// @brief Tick per seconds of the server
            float _tps = 0;

            /// @brief Saved value to update the delta time
            std::chrono::steady_clock::time_point _lastUpdate;
            rtp::UDPServer &_udp;
    };
} // namespace rtp

#endif /* !SERVERSYSTEM_HPP_ */
