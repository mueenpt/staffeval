#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"

#include <iostream>


void handleNick(Server &server, int fd, const std::string &line)
{
    // Need a nickname parameter
    if (line.size() <= 5)
    {
        server.sendMessage(fd,
            ":ircserv 431 * :No nickname given\r\n");
        return;
    }

    std::string nick = Parser::trim(line.substr(5));

    // Handle "NICK    "
    if (nick.empty())
    {
        server.sendMessage(fd,
            ":ircserv 431 * :No nickname given\r\n");
        return;
    }

    if (!Parser::isValidNickname(nick))
    {
        CommandReplies::invalidNick(server, fd, nick);
        return;
    }

    if (server.isNicknameTaken(nick, fd))
    {
        server.sendMessage(fd,
            ":ircserv 433 " + nick + " :Nickname is already in use\r\n");
        return;
    }

    server.getClient(fd)->setNickname(nick);

    std::cout << "Nickname set to: " << nick << std::endl;

    server.checkRegistration(fd);
}


// void handleNick(Server &server, int fd, const std::string &line)
// {
//     std::string nick = Parser::trim(line.substr(5));

//     if (nick.empty())
//     {
//         server.sendMessage(fd, ":ircserv 431 * :No nickname given\r\n");
//         return;
//     }

//     if (!Parser::isValidNickname(nick))
//     {
//         CommandReplies::invalidNick(server, fd, nick);
//         return;
//     }

//     if (server.isNicknameTaken(nick, fd))
//     {
//         server.sendMessage(fd, ":ircserv 433 " + nick + " :Nickname is already in use\r\n");
//         return;
//     }

//     server.getClient(fd)->setNickname(nick);

//     std::cout << "Nickname set to: " << nick << std::endl;
//     server.checkRegistration(fd);
// }
