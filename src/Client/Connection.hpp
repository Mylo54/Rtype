/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Connection
*/

#ifndef CONNECTION_HPP_
#define CONNECTION_HPP_

#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>
#include "../Components/Components.hpp"
#include "../ClientSystems/ClientSystems.hpp"
#include "../ClientSystems/NetworkSystems.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include "../NetworkStructs.hpp"
#include <memory>
#include "Miscellaneous.hpp"

namespace rtp {
    class Connection {
        public:
            /// @brief Connection object constructor
            /// @param manager reference to registry manager
            /// @param co function connect
            Connection(eng::RegistryManager &manager,
            eng::TextureManager &textureManager);
            ~Connection();

            eng::Entity addPlayer(eng::Registry &reg, int playerId, int syncId);
        protected:
            /// @brief Add layers of backgrounds to a registry
            /// @param reg The Registry on which to add the backgrounds
            void _addBackgrounds(eng::Registry &reg);

            void _addButtonStart(eng::Registry &r);
            int _btnFctStart(eng::RegistryManager &reg);
        private:
            eng::RegistryManager &_manager;
            eng::TextureManager &_textureManager;
    };
}

#endif /* !Connection_HPP_ */
