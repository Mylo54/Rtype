/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../Components/ClientComps.hpp"
#include "../ClientSystems/Systems.hpp"
#include "../Engine/RegistryManager.hpp"

namespace rtp {

    enum ACTIONTYPE_PREGAME {
        OK,
        KO,
        CONNECT,
        CREATE_LOBBY,
        LIST_LOBBIES,
        JOIN_LOBBY,
        PLAYER_JOINED_LOBBY,
        START_GAME
    };

    enum ACTIONTYPE_INGAME {
        UP,
        RIGHT,
        DOWN,
        LEFT,
        SHOT,
        QUIT
    };

    typedef struct payload {
        int ACTION_NAME;
        size_t bodySize = 0;
        void * body = NULL;
    } networkPayload;

    class Client {
        public:
            Client(int port);
            ~Client();
            void run();
            void systemsLoop();
            void send();
        protected:
        private:
            /// @brief Setup the registry with every sparse array needed
            /// @param r The Registry to setup
            void _setupRegistry(eng::Registry &reg);

            /// @brief Adds a controllable player to a registry
            /// @param reg The Registry on which to adds the player 
            /// @return The entity containing the player
            eng::Entity _addPlayer(eng::Registry &reg);

            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            /// @return A vector of entities, each representing a background
            std::vector<eng::Entity> _addBackgrounds(eng::Registry &reg);
            eng::RegistryManager _manager;
            int _port;
    };
}

#endif /* !CLIENT_HPP_ */
