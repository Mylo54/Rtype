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
            void receiveData(eng::Registry &r);
        protected:
        private:
            rtp::UDPServer &_udp;
    };
} // namespace rtp

#endif /* !SERVERSYSTEM_HPP_ */
