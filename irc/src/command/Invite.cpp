#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>

void handleInvite(Server &server, int fd, const std::string &line)
{
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 3)
    {
        CommandReplies::needMoreParams(server, fd, "INVITE");
        return;
    }

    std::string targetNick = tokens[1];
    std::string channelName = tokens[2];

    Channel *channel = server.findChannel(channelName);
    if (!channel)
    {
        CommandReplies::noSuchChannel(server, fd, channelName);
        return;
    }
    if (!channel->hasMember(fd, server.getNickname(fd)))
    {
        CommandReplies::notOnChannel(server, fd, channelName);
        return;
    }
    if (channel->isInviteOnly() && !channel->isOperator(fd))
    {
        CommandReplies::chanOpPrivNeeded(server, fd, channelName);
        return;
    }

    int targetFd = server.getFdByNickname(targetNick);
    if (targetFd < 0)
    {
        CommandReplies::noSuchNick(server, fd, targetNick);
        return;
    }
    if (channel->hasMember(targetFd, targetNick))
    {
        server.sendMessage(fd, ":ircserv 443 " + targetNick + " " + channelName + " :is already on channel\r\n");
        return;
    }

    channel->invite(targetFd, targetNick);
    server.sendMessage(fd, ":ircserv 341 " + server.getNickname(fd) + " " + targetNick + " " + channelName + "\r\n");
    server.sendMessage(targetFd, ":" + server.makePrefix(fd) + " INVITE " + targetNick + " :" + channelName + "\r\n");
}
