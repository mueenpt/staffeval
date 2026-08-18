#include "CommandHandlers.hpp"
#include "Parser.hpp"
#include "Server.hpp"

void handleQuit(Server &server, int fd, const std::string &line)
{
    std::string reason = Parser::takeTrailingMessage(line);
    if (reason.empty())
        reason = "Leaving";

    std::string quitMsg = ":" + server.makePrefix(fd) + " QUIT :" + reason + "\r\n";
    server.broadcastQuit(fd, quitMsg);
    server.disconnectClient(fd);
}
