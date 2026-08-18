#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>

void handleTopic(Server &server, int fd, const std::string &line)
{
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 2)
    {
        CommandReplies::needMoreParams(server, fd, "TOPIC");
        return;
    }

    std::string channelName = tokens[1];
    Channel *channel = server.findChannel(channelName);
    if (!channel)
    {
        CommandReplies::noSuchChannel(server, fd, channelName);
        return;
    }
    if (!channel->hasMember(fd))
    {
        CommandReplies::notOnChannel(server, fd, channelName);
        return;
    }

    size_t topicPos = line.find(" :");
    if (topicPos == std::string::npos)
    {
        if (channel->getTopic().empty())
            server.sendMessage(fd, ":ircserv 331 " + server.getNickname(fd) + " " + channelName + " :No topic is set\r\n");
        else
            server.sendMessage(fd, ":ircserv 332 " + server.getNickname(fd) + " " + channelName + " :" + channel->getTopic() + "\r\n");
        return;
    }

    if (channel->isTopicRestricted() && !channel->isOperator(fd))
    {
        CommandReplies::chanOpPrivNeeded(server, fd, channelName);
        return;
    }

    std::string newTopic = line.substr(topicPos + 2);
    channel->setTopic(newTopic);
    server.broadcastToChannel(channelName, ":" + server.makePrefix(fd) + " TOPIC " + channelName + " :" + newTopic + "\r\n", -1);
}
