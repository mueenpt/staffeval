#ifndef COMMAND_REPLIES_HPP
#define COMMAND_REPLIES_HPP

#include <string>
#include "Server.hpp"

namespace CommandReplies
{
    inline void noSuchChannel(Server &server, int fd, const std::string &channel)
    {
        server.sendMessage(fd, ":ircserv 403 " + channel + " :No such channel\r\n");
    }

    inline void needMoreParams(Server &server, int fd, const std::string &cmd)
    {
        server.sendMessage(fd, ":ircserv 461 " + cmd + " :Not enough parameters\r\n");
    }

    inline void notOnChannel(Server &server, int fd, const std::string &channel)
    {
        server.sendMessage(fd, ":ircserv 442 " + channel + " :You're not on that channel\r\n");
    }

    inline void chanOpPrivNeeded(Server &server, int fd, const std::string &channel)
    {
        server.sendMessage(fd, ":ircserv 482 " + channel + " :You're not channel operator\r\n");
    }

    inline void noSuchNick(Server &server, int fd, const std::string &nick)
    {
        server.sendMessage(fd, ":ircserv 401 " + nick + " :No such nick\r\n");
    }

    inline void invalidNick(Server &server, int fd, const std::string &nick)
    {
        server.sendMessage(fd, ":ircserv 432 " + nick + " :Erroneous nickname\r\n");
    }
}

#endif