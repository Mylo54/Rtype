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
#include <boost/asio.hpp>
#include <string.h>

#include "../Components/Components.hpp"
#include "../SystemsServer/SystemsServer.hpp"
#include "../Engine/Registry.hpp"
#include "../Engine/IRegistry.hpp"
#include "../Engine/RegistryManager.hpp"

namespace rtp {
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
