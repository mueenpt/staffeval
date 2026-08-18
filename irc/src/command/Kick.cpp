#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>

void handleKick(Server &server, int fd, const std::string &line)
{
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 3)
    {
        CommandReplies::needMoreParams(server, fd, "KICK");
        return;
    }

    std::string channelName = tokens[1];
    std::string targetNick = tokens[2];
    std::string reason = Parser::takeTrailingMessage(line);
    if (reason.empty())
        reason = "Kicked";

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
    if (!channel->isOperator(fd))
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
    if (!channel->hasMember(targetFd, targetNick))
    {
        server.sendMessage(fd, ":ircserv 441 " + targetNick + " " + channelName + " :They aren't on that channel\r\n");
        return;
    }

    std::string msg = ":" + server.makePrefix(fd) + " KICK " + channelName + " " + targetNick + " :" + reason + "\r\n";
    server.broadcastToChannel(channelName, msg, -1);
    channel->removeMember(targetFd, targetNick);
    if (channel->empty())
        server.eraseChannel(channelName);
}
