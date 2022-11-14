/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** WaitingRoom
*/

#ifndef WAITINGROOM_HPP_
#define WAITINGROOM_HPP_

#include <iostream>
#include <fstream>
#include <memory>
#include "AScene.hpp"
#include "../GameComponent/Button.hpp"
#include "../GameComponent/Background.hpp"
#include "../System/ButtonSystem.hpp"

namespace rtp {
    class WaitingRoom : public AScene {
        public:
            WaitingRoom(rtp::scene_package_t pack);
            ~WaitingRoom();
            
            void setupScene() override;
            void setupRegistry() override;
            void systemRun() override;
            eng::Entity addPlayer(int playerId, int syncId);
        protected:
            void _addBackgrounds();
            void _addButtonStart();
            int _btnFctStart();
            void sendData();
        private:
    };
}

#endif /* !WAITINGROOM_HPP_ */
