#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>

void handlePrivmsg(Server &server, int fd, const std::string &line)
{
    Client *client = server.getClient(fd);

    if (!client->isRegistered())
    {
        server.sendMessage(fd,
            ":ircserv 451 :You have not registered\r\n");
        return;
    }
    
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 2)
    {
        CommandReplies::needMoreParams(server, fd, "PRIVMSG");
        return;
    }

    std::string target = tokens[1];
    std::string message = Parser::takeTrailingMessage(line);
    if (message.empty())
    {
        server.sendMessage(fd, ":ircserv 412 :No text to send\r\n");
        return;
    }

    std::string payload = ":" + server.makePrefix(fd) + " PRIVMSG " + target + " :" + message + "\r\n";
    if (!target.empty() && target[0] == '#')
    {
        Channel *channel = server.findChannel(target);
        if (!channel)
        {
            CommandReplies::noSuchChannel(server, fd, target);
            return;
        }
        if (!channel->hasMember(fd, client->getNickname()))
        {
            CommandReplies::notOnChannel(server, fd, target);
            return;
        }
        server.broadcastToChannel(target, payload, fd);
        return;
    }

    int targetFd = server.getFdByNickname(target);
    if (targetFd < 0)
    {
        CommandReplies::noSuchNick(server, fd, target);
        return;
    }
    server.sendMessage(targetFd, payload);
}
