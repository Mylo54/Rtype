/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** Server 
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <locale>
#include <string.h>


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace rt {
    class Server {
        public:
            Server(int port);
            ~Server();

            void run();

            // Liste des méthodes à implémenter :


        protected:
        private:
    };
};

#endif /* !SERVER_HPP_ */
