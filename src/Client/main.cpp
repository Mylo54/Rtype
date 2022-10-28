/*
** EPITECH PROJECT, 2022
** src
** File description:
** main
*/

#include "Client.hpp"

/*
eng::Entity makeEnemy(eng::Registry &r, sf::RenderWindow &w, sf::Clock &c)
{
    eng::Entity res = r.spawnEntity();

    r.addComponent<rtp::Position>(res, rtp::Position(1920, rand() % 1080, 0));
    r.addComponent<rtp::Velocity>(res, rtp::Velocity(-5, 0));
    r.addComponent<rtp::Drawable>(res, rtp::Drawable("../assets/flyers.png" 3, sf::IntRect(0, 0, 40, 16), 0.005));

    r.getComponents<rtp::Drawable>()[res.getId()].value().sprite.setScale(2, 2);
    return res;
}*/

int main(int argc, char **argv)
{
    srand(time(NULL));
    if (argc != 3) {
        std::cout << "not enough arguments (awaiting ip and port)" << std::endl;
        return (84);
    }
    //boost::asio::ip::port_type port = 3305;
    std::string serverAddr(argv[1]);
    boost::asio::ip::port_type port = atoi(argv[2]);
    std::cout << "DEBUG001 : serverAddr : {" << serverAddr << "} port : " << port << std::endl;

    rtp::Client client(port, serverAddr);

    client.run();
    /*
    for (int i = 1; i < argc; i++)
        if (strcmp(argv[i], "-debug") == 0) {
            manage.setDebugMode(true);
            manage.createLogPath();
        }
    */
    return 0;
}