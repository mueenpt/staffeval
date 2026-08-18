#include "Server.hpp"
#include <iostream>
#include <cstdlib>

bool parsePort(const char *str, int &port)
{
    char *end;

    port = std::strtol(str, &end, 10);

    if (*end != '\0')
        return false;

    if (port < 1 || port > 65535)
        return false;

    return true;
}

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: ./ircserv <port> <password>" << std::endl;
        return (1);
    }

    try
    {
        int port;

        if (!parsePort(argv[1], port))
        {
            std::cerr << "Error: Invalid port" << std::endl;
            return (1);
        }

        std::string password = argv[2];

        Server server(port, password);

        server.setupSocket();
        server.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return (1);
    }

    return (0);
}