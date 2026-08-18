#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>
#include <cstdlib>

void handleMode(Server &server, int fd, const std::string &line)
{
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 2)
    {
        CommandReplies::needMoreParams(server, fd, "MODE");
        return;
    }

    std::string channelName = tokens[1];

    if (channelName.empty() || channelName[0] != '#')
        return;
        
    Channel *channel = server.findChannel(channelName);
    if (!channel)
    {
        CommandReplies::noSuchChannel(server, fd, channelName);
        return;
    }

    if (tokens.size() == 2)
    {
        std::string modes = "+";
        if (channel->isInviteOnly()) modes += "i";
        if (channel->isTopicRestricted()) modes += "t";
        if (channel->hasKey()) modes += "k";
        if (channel->hasUserLimit()) modes += "l";
        server.sendMessage(fd, ":ircserv 324 " + server.getNickname(fd) + " " + channelName + " " + modes + "\r\n");
        return;
    }

    if (!channel->hasMember(fd))
    {
        CommandReplies::notOnChannel(server, fd, channelName);
        return;
    }
    if (!channel->isOperator(fd))
    {
        CommandReplies::chanOpPrivNeeded(server, fd, channelName);
        return;
    }

    std::string modeString = tokens[2];
    bool adding = true;
    size_t paramIndex = 3;

    for (size_t i = 0; i < modeString.size(); ++i)
    {
        char m = modeString[i];
        if (m == '+') { adding = true; continue; }
        if (m == '-') { adding = false; continue; }

        if (m == 'i') channel->setInviteOnly(adding);
        else if (m == 't') channel->setTopicRestricted(adding);
        else if (m == 'k')
        {
            if (adding)
            {
                if (paramIndex >= tokens.size()) { CommandReplies::needMoreParams(server, fd, "MODE"); return; }
                channel->setKey(tokens[paramIndex++]);
            }
            else channel->clearKey();
        }
        else if (m == 'o')
        {
            if (paramIndex >= tokens.size()) { CommandReplies::needMoreParams(server, fd, "MODE"); return; }
            std::string nick = tokens[paramIndex++];
            int targetFd = server.getFdByNickname(nick);
            if (targetFd < 0 || !channel->hasMember(targetFd)) { server.sendMessage(fd, ":ircserv 441 " + nick + " " + channelName + " :They aren't on that channel\r\n"); return; }
            if (adding) channel->addOperator(targetFd); else channel->removeOperator(targetFd);
        }
        else if (m == 'l')
        {
            if (adding)
            {
                if (paramIndex >= tokens.size()) { CommandReplies::needMoreParams(server, fd, "MODE"); return; }
                int limit = std::atoi(tokens[paramIndex++].c_str());
                if (limit <= 0) { server.sendMessage(fd, ":ircserv 696 " + channelName + " l :Invalid limit\r\n"); return; }
                channel->setUserLimit(limit);
            }
            else channel->clearUserLimit();
        }
        else
        {
            server.sendMessage(fd, ":ircserv 472 " + std::string(1, m) + " :is unknown mode char to me\r\n");
            return;
        }
    }

    std::string announce = ":" + server.makePrefix(fd) + " MODE " + channelName + " " + modeString;
    for (size_t p = 3; p < tokens.size(); ++p)
        announce += " " + tokens[p];
    announce += "\r\n";
    server.broadcastToChannel(channelName, announce, -1);
}
