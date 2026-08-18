#include "CommandHandlers.hpp"
#include "CommandReplies.hpp"
#include "Parser.hpp"
#include "Server.hpp"
#include "Channel.hpp"

#include <vector>

void handlePart(Server &server, int fd, const std::string &line)
{
    std::vector<std::string> tokens = Parser::splitSpaces(line);
    if (tokens.size() < 2)
    {
        CommandReplies::needMoreParams(server, fd, "PART");
        return;
    }

    std::string channelList = tokens[1];
    std::string reason = Parser::takeTrailingMessage(line);

    size_t pos = 0;
    while (pos < channelList.size())
    {
        size_t comma = channelList.find(',', pos);
        if (comma == std::string::npos)
            comma = channelList.size();

        std::string channelName = channelList.substr(pos, comma - pos);
        Channel *channel = server.findChannel(channelName);
        if (!channel)
            CommandReplies::noSuchChannel(server, fd, channelName);
        else if (!channel->hasMember(fd, server.getNickname(fd)))
            CommandReplies::notOnChannel(server, fd, channelName);
        else
        {
            std::string msg = ":" + server.makePrefix(fd) + " PART " + channelName;
            if (!reason.empty()) msg += " :" + reason;
            msg += "\r\n";
            server.broadcastToChannel(channelName, msg, -1);
            channel->removeMember(fd, server.getNickname(fd));
            if (channel->empty())
                server.eraseChannel(channelName);
        }

        pos = comma + 1;
    }
}
