/*
** EPITECH PROJECT, 2022
** rtype
** File description:
** mainServer
*/


#include "Server.hpp"

int errorManagement(int ac, char **av)
{
    if (ac != 2)
        return(84);
    for (int i = 0; i < strlen(av[1]); i++) {
        if(!isdigit(av[1][i])) {
            std::cout << "PORT format is not correct according to syntax\n";
            return (84);
        }
    }
    return(0);
}

int printHelp()
{
    std::cout << "[RTYPE - SERVER]" << std::endl;
    std::cout << "\t./RType-Server [port]" << std::endl;
    std::cout << "[port]: the port you want to open for the clients to connect" << std::endl;
    return (0);
}

int main(int ac, char **av)
{
    std::string arg;


    if (ac >= 2) {
        arg = av[1];
        if ((arg == "-h" || arg == "-help"))
            return (printHelp());
    }
    try {

        // GETTING IP
        // boost::asio::io_service netService;
        // boost::asio::ip::udp::resolver   resolver(netService);
        // boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "google.com", "");
        // boost::asio::ip::udp::resolver::iterator endpoints = resolver.resolve(query);
        // boost::asio::ip::udp::endpoint ep = *endpoints;
        // boost::asio::ip::udp::socket socket(netService);
        // socket.connect(ep);
        // boost::asio::ip::address addr = socket.local_endpoint().address();
        // std::cout << "My IP according to google is: " << addr.to_string() << std::endl;



        boost::asio::ip::port_type port(3305);
        rtp::Server srv(port);
        srv.run();
    }
    catch (const std::exception &error) {
        std::cerr << error.what() << std::endl;
    }
    return (0);
}
