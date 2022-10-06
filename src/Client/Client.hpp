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
#include <string>
#include <vector>
#include <list>
#include <boost/asio.hpp>

namespace rtp {
    class Client {
        public:
            Client(int port);
            ~Client();
            void run();
        protected:
        private:
    };
}

#endif /* !CLIENT_HPP_ */
