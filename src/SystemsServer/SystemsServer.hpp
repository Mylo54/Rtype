/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** SystemsServer
*/

#ifndef SYSTEMSSERVER_HPP_
#define SYSTEMSSERVER_HPP_


#include "../Engine/Registry.hpp"
#include "../Components/Components.hpp"

namespace rtp {
    class SystemsServer {
        public:
            SystemsServer();
            ~SystemsServer();

            /// @brief A system who applies velocities on positions
            /// @param r The Registry on which to apply the system 
            void positionSystem(eng::Registry &r);

            /// @brief A system who handles inputs and stores actions
            /// @param r The Registry on which to apply the system 
            void controlSystem(eng::Registry &r);

            /// @brief A system who handle movement on controllable entities
            /// @param r The registry on which to apply the system
            void controlMovementSystem(eng::Registry &r);

            /// @brief A system who handles inputs for shooting
            /// @param r The registry on which to apply the system
            void controlFireSystem(eng::Registry &r);

            /// @brief A system which sends data to the server
            /// @param r The Registry on which to apply the system
            void sendData(eng::Registry &r);
            
            /// @brief A system which receive and write data in the registry
            /// @param r The Registry on which to apply the system
            void receiveData(eng::Registry &r);
        protected:
        private:
    };
};

#endif /* !SYSTEMSSERVER_HPP_ */