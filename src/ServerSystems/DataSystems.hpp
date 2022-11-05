/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataSystems
*/

#ifndef DATASYSTEMS_HPP_
#define DATASYSTEMS_HPP_

#include "../NetworkStructs.hpp"
#include <EngineCoreSuper/EngineCoreSuper.hpp>
#include <vector>
#include <thread>
#include <condition_variable>
#include <boost/asio.hpp>
#include "../Components/Components.hpp"

namespace rtp
{
    class DataSystems {
        public:
            DataSystems(std::mutex &dataMutex,
            std::vector<std::vector<int>> &payloadList,
            boost::asio::ip::udp::socket &socket,
            std::vector<boost::asio::ip::udp::endpoint> &endpoints);
            ~DataSystems();

            /// @brief A system for sending data from r to the clients
            /// @param r The registry
            void sendData(eng::Registry &r);

            /// @brief A system for writing the data inside _payloadList in r
            /// @param r The Registry
            void receiveData(eng::Registry &r);
        protected:
        private:
            /// @brief Method to send the data contained in vector to all clients
            /// @param vector A vector containing data
            void _sendDataToAll(std::vector<int> &vector);

            /// @brief atomic variable to access payloadList
            std::mutex &_dataMutex;

            /// @brief list of payloads
            std::vector<std::vector<int>> &_payloadList;

            /// @brief data sending socket
            boost::asio::ip::udp::socket &_socket;

            /// @brief list (vector) of client endpoints
            std::vector<boost::asio::ip::udp::endpoint> &_endpoints;
    };
} // namespace rtp

#endif /* !DATASYSTEMS_HPP_ */
