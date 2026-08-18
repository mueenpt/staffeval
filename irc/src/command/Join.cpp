#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <map>
#include <string>

void handleJoin(Server &server, int fd, const std::string &line)
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
        CommandReplies::needMoreParams(server, fd, "JOIN");
        return;
    }

    std::string channelName = tokens[1];

    if (channelName.empty() || channelName == ":")
    {
        CommandReplies::needMoreParams(server, fd, "JOIN");
        return;
    }

    std::string providedKey;
    if (tokens.size() >= 3)
        providedKey = tokens[2];

    if (!Parser::isValidChannelName(channelName))
    {
        server.sendMessage(fd, ":ircserv 476 " + channelName + " :Bad Channel Mask\r\n");
        return;
    }

    std::map<std::string, Channel> &channels = server.getChannels();
    std::map<std::string, Channel>::iterator it = channels.find(channelName);
    if (it == channels.end())
    {
        channels[channelName] = Channel(channelName);
        it = channels.find(channelName);
        it->second.addOperator(fd);
    }

    Channel &channel = it->second;
    if (channel.hasMember(fd, client->getNickname()))
        return;

    if (channel.isInviteOnly() && !channel.isInvited(fd, client->getNickname()))
    {
        server.sendMessage(fd, ":ircserv 473 " + channelName + " :Cannot join channel (+i)\r\n");
        return;
    }
    if (channel.hasKey() && channel.getKey() != providedKey)
    {
        server.sendMessage(fd, ":ircserv 475 " + channelName + " :Cannot join channel (+k)\r\n");
        return;
    }
    if (channel.hasUserLimit() && channel.memberCount() >= static_cast<size_t>(channel.getUserLimit()))
    {
        server.sendMessage(fd, ":ircserv 471 " + channelName + " :Cannot join channel (+l)\r\n");
        return;
    }

    channel.addMember(fd, client->getNickname());
    channel.revokeInvite(fd, client->getNickname());

    std::string joinMsg = ":" + server.makePrefix(fd) + " JOIN " + channelName + "\r\n";
    server.broadcastToChannel(channelName, joinMsg, -1);

    if (!channel.getTopic().empty())
        server.sendMessage(fd, ":ircserv 332 " + server.getNickname(fd) + " " + channelName + " :" + channel.getTopic() + "\r\n");
    else
        server.sendMessage(fd, ":ircserv 331 " + server.getNickname(fd) + " " + channelName + " :No topic is set\r\n");
}
