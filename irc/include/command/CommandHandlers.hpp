#ifndef COMMAND_HANDLERS_HPP
#define COMMAND_HANDLERS_HPP

#include <string>

class Server;

void handlePass(Server &server, int fd, const std::string &line);
void handleNick(Server &server, int fd, const std::string &line);
void handleUser(Server &server, int fd, const std::string &line);
void handleJoin(Server &server, int fd, const std::string &line);
void handlePrivmsg(Server &server, int fd, const std::string &line);
void handleKick(Server &server, int fd, const std::string &line);
void handleInvite(Server &server, int fd, const std::string &line);
void handleTopic(Server &server, int fd, const std::string &line);
void handleMode(Server &server, int fd, const std::string &line);
void handlePart(Server &server, int fd, const std::string &line);
void handleQuit(Server &server, int fd, const std::string &line);

#endif