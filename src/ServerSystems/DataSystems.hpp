/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** DataSystems
*/

#ifndef DATASYSTEMS_HPP_
#define DATASYSTEMS_HPP_

#include <vector>
#include <thread>

namespace rtp
{
    class DataSystems {
        public:
            DataSystems();
            ~DataSystems();

        protected:
        private:
            /// @brief atomic variable to access payloadList
            std::mutex &_dataMutex;
            /// @brief list of payloads
            std::vector<std::vector<int>> &_payloadList;
    };
} // namespace rtp

#endif /* !DATASYSTEMS_HPP_ */
