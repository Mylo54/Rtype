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

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace rt {
    class Client {
        public:
            Client(int port);
            ~Client();

            void run();
        private:
        protected:
    };
};


#endif /* !CLIENT_HPP_ */