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

            /// @brief A system who logs the infos of players
            /// @param r The Registry on which to apply the system 
            void playerLogSystem(eng::Registry &r);
            
            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

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
        protected:
        private:
            /// @brief A method that gets a synced entity id
            /// @param syncId The synced component id
            /// @return The entity id
            int _getSyncedEntity(eng::Registry &r, int syncId);

            /// @brief A method for sending a package to every endpoint
            /// @todo find how to contain the data that we need to send to the client
            void _sendSubsystem();

            /// @brief data sending socket
            boost::asio::ip::udp::socket &_socket;
            /// @brief list (vector) of client endpoints
            std::vector<boost::asio::ip::udp::endpoint> &_endpoints;
            /// @brief atomic variable of acces to listDataRec
            std::mutex &_mutex;
            /// @brief List of all received payload
            std::vector<inputPayload_t> &_listDataRec;
            /// @brief 
            std::clock_t _clock;
            /// @brief delta time in seconds
            float _delta;
    };
};

#endif /* !SERVERSYSTEMS_HPP_ */
