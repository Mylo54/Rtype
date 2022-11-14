/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** ClientSystem
*/

#ifndef CLIENTSYSTEM_HPP_
#define CLIENTSYSTEM_HPP_

#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../Network/UDPClient.hpp"

namespace rtp
{
    enum syncedComponent{
        position,
        velocity,
        playerStats,
        enemyStats
    };
    class ClientSystem {
        public:
            ClientSystem(rtp::UDPClient &client);
            ~ClientSystem();

            void sendInputData(eng::Registry &reg);
            void receiveData(eng::Registry &reg, eng::TextureManager &tm);
        protected:
        private:
            rtp::UDPClient &_udp;
    };
} // namespace rtp



#endif /* !CLIENTSYSTEM_HPP_ */
