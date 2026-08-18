#include "CommandHandlers.hpp"
#include "Parser.hpp"
#include "Server.hpp"

#include <sstream>
#include <iostream>

void handleUser(Server &server, int fd, const std::string &line)
{
    Client *client = server.getClient(fd);

    // USER cannot be sent after registration
    if (client->isRegistered())
    {
        server.sendMessage(fd,
            ":ircserv 462 :You may not reregister\r\n");
        return;
    }

    // Need parameters after USER
    if (line.size() <= 5)
    {
        server.sendMessage(fd,
            ":ircserv 461 USER :Not enough parameters\r\n");
        return;
    }

    std::string userPart = line.substr(5);
    std::istringstream iss(userPart);

    std::string username;
    std::string mode;
    std::string unused;
    std::string realname;

    if (!(iss >> username >> mode >> unused))
    {
        server.sendMessage(fd,
            ":ircserv 461 USER :Not enough parameters\r\n");
        return;
    }

    std::getline(iss, realname);

    size_t colonPos = realname.find(':');
    if (colonPos == std::string::npos)
    {
        server.sendMessage(fd,
            ":ircserv 461 USER :Not enough parameters\r\n");
        return;
    }

    realname = Parser::trim(realname.substr(colonPos + 1));

    if (realname.empty())
    {
        server.sendMessage(fd,
            ":ircserv 461 USER :Not enough parameters\r\n");
        return;
    }

    client->setUsername(username);

    std::cout << "Username set to: " << username << std::endl;

    server.checkRegistration(fd);
}


// void handleUser(Server &server, int fd, const std::string &line)
// {
//     std::string userPart = line.substr(5);
//     std::istringstream iss(userPart);
//     std::string username, mode, unused, realname;

//     iss >> username;
//     if (username.empty())
//     {
//         server.sendMessage(fd, ":ircserv 461 USER :Not enough parameters\r\n");
//         return;
//     }

//     iss >> mode >> unused;
//     std::getline(iss, realname);
//     size_t colonPos = realname.find(':');
//     if (colonPos != std::string::npos)
//         realname = realname.substr(colonPos + 1);
//     while (!realname.empty() && (realname[0] == ' ' || realname[0] == '\t'))
//         realname.erase(0, 1);

//     server.getClient(fd)->setUsername(username);
//     std::cout << "Username set to: " << username << std::endl;
//     server.checkRegistration(fd);
// }
