#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"

#include <iostream>

void handlePass(Server &server, int fd, const std::string &line)
{
    Client *client = server.getClient(fd);

    // PASS cannot be sent after registration
    if (client->isRegistered())
    {
        server.sendMessage(fd,
            ":ircserv 462 :You may not reregister\r\n");
        return;
    }

    // PASS already successfully given
    if (client->isPasswordOk())
    {
        server.sendMessage(fd,
            ":ircserv 462 :You may not reregister\r\n");
        return;
    }

    // Need a password parameter
    if (line.size() <= 5)
    {
        server.sendMessage(fd,
            ":ircserv 461 PASS :Not enough parameters\r\n");
        return;
    }

    std::string pass = Parser::trim(line.substr(5));

    // Handle "PASS    "
    if (pass.empty())
    {
        server.sendMessage(fd,
            ":ircserv 461 PASS :Not enough parameters\r\n");
        return;
    }

    if (pass == server.getPassword())
    {
        client->setPasswordOk(true);
        server.sendMessage(fd, "Password accepted\r\n");
        server.checkRegistration(fd);
    }
    else
    {
        server.sendMessage(fd,
            ":ircserv 464 :Password incorrect\r\n");
    }
}


// void handlePass(Server &server, int fd, const std::string &line)
// {
//     std::string pass = Parser::trim(line.substr(5));

//     if (pass == server.getPassword())
//     {
//         server.getClient(fd)->setPasswordOk(true);
//         server.sendMessage(fd, "Password accepted\r\n");
//         server.checkRegistration(fd);
//     }
//     else
//     {
//         std::cout << "Wrong password" << std::endl;
//         server.sendMessage(fd, ":ircserv 464 * :Password incorrect\r\n");
//     }
// }
