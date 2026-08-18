#include "Server.hpp"
#include "CommandHandlers.hpp"
#include "Parser.hpp"

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sstream>
#include <cctype>

#include <unistd.h>
#include <fcntl.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

Server::Server(int port, const std::string &password)
    : server_fd(-1),
      port(port),
      password(password)
{
}

const std::string &Server::getPassword() const
{
    return password;
}

Server::~Server()
{
    if (server_fd != -1)
        close(server_fd);
}

void Server::setupSocket()
{
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd < 0)
        throw std::runtime_error("socket failed");

    int opt = 1;

    if (setsockopt(server_fd,
                   SOL_SOCKET,
                   SO_REUSEADDR,
                   &opt,
                   sizeof(opt)) < 0)
        throw std::runtime_error("setsockopt failed");

    sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(server_fd,
             (sockaddr *)&server_addr,
             sizeof(server_addr)) < 0)
        throw std::runtime_error("bind failed");

    if (listen(server_fd, SOMAXCONN) < 0)
        throw std::runtime_error("listen failed");

    if (fcntl(server_fd, F_SETFL, O_NONBLOCK) < 0)
        throw std::runtime_error("fcntl failed");

    std::cout << "Server listening on port "
              << port << std::endl;
}
void Server::run()
{
    pollfd server_poll;

    server_poll.fd = server_fd;
    server_poll.events = POLLIN;
    server_poll.revents = 0;

    poll_fds.push_back(server_poll);

    while (true)
    {
        int ready = poll(&poll_fds[0],
                         poll_fds.size(),
                         -1);

        if (ready < 0)
            throw std::runtime_error("poll failed");

        for (size_t i = 0; i < poll_fds.size(); ++i)
        {
            if (!(poll_fds[i].revents & POLLIN))
                continue;

            if (poll_fds[i].fd == server_fd)
            {
                int client_fd = accept(server_fd, NULL, NULL);

                if (client_fd < 0)
                    continue;

                if (fcntl(client_fd, F_SETFL, O_NONBLOCK) < 0)
                {
                    close(client_fd);
                    continue;
                }

                pollfd client_poll;
                client_poll.fd = client_fd;
                client_poll.events = POLLIN;
                client_poll.revents = 0;

                poll_fds.push_back(client_poll);

                clients[client_fd] = Client(client_fd);

                std::cout << "Client connected: "
                          << client_fd
                          << std::endl;
            }
            else
            {
                char buffer[1024];

                ssize_t bytes = recv(
                    poll_fds[i].fd,
                    buffer,
                    sizeof(buffer) - 1,
                    0);

                if (bytes <= 0)
                {
                    removeClient(i);
                    --i;
                    continue;
                }

                buffer[bytes] = '\0';

                Client &client = clients[poll_fds[i].fd];

                client.appendBuffer(buffer);

                std::string &data = client.getBuffer();

                size_t pos;

                while ((pos = data.find('\n')) != std::string::npos)
                {
                    std::string command = data.substr(0, pos);

                    if (!command.empty() &&
                        command[command.size() - 1] == '\r')
                        command.erase(command.size() - 1);

                    data.erase(0, pos + 1);

                    handleCommand(poll_fds[i].fd, command);
                }
            }
        }
    }
}

void Server::handleCommand(int fd,
                           const std::string &command)
{
    std::string cmd = Parser::trim(command);

    size_t spacePos = cmd.find(' ');
    if (spacePos != std::string::npos)
        cmd = cmd.substr(0, spacePos);

    cmd = Parser::toUpper(cmd);

    // Ignore IRCv3 capability negotiation
    if (cmd == "CAP")
        return;

    if (cmd == "PASS")
        return handlePass(*this, fd, command);

    if (cmd == "NICK")
        return handleNick(*this, fd, command);

    if (cmd == "USER")
        return handleUser(*this, fd, command);

    Client *client = getClient(fd);

    if (!client)
        return;

    if (cmd == "PING")
    {
        std::string payload = Parser::trim(command.substr(4));

        if (!payload.empty())
            sendMessage(fd,
                ":ircserv PONG ircserv :" + payload + "\r\n");

        return;
    }

    if (!client->isRegistered() &&
        cmd != "QUIT" &&
        cmd != "PONG")
    {
        sendMessage(fd,
            ":ircserv 451 * :You have not registered\r\n");
        return;
    }

    if (cmd == "QUIT")
        return handleQuit(*this, fd, command);

    if (cmd == "JOIN")
        return handleJoin(*this, fd, command);

    if (cmd == "PRIVMSG")
        return handlePrivmsg(*this, fd, command);

    if (cmd == "KICK")
        return handleKick(*this, fd, command);

    if (cmd == "INVITE")
        return handleInvite(*this, fd, command);

    if (cmd == "TOPIC")
        return handleTopic(*this, fd, command);

    if (cmd == "MODE")
        return handleMode(*this, fd, command);

    if (cmd == "PART")
        return handlePart(*this, fd, command);

    if (cmd == "PONG")
        return;

    sendMessage(fd,
        ":ircserv 421 " + cmd + " :Unknown command\r\n");
}

void Server::checkRegistration(int fd)
{
    Client &client = clients[fd];

    if (client.isRegistered())
        return;

    if (client.isPasswordOk()
        && !client.getNickname().empty()
        && !client.getUsername().empty())
    {
        client.setRegistered(true);

        sendMessage(
            fd,
            ":ircserv 001 " + client.getNickname() + " :Welcome to ft_irc\r\n");

        std::cout
            << "Client "
            << fd
            << " registered!"
            << std::endl;
    }
}

void Server::sendMessage(
    int fd,
    const std::string &message)
{
    send(
        fd,
        message.c_str(),
        message.size(),
        0);
}

void Server::removeClient(size_t index)
{
    int fd = poll_fds[index].fd;

    std::cout
        << "Client disconnected: "
        << fd
        << std::endl;

    close(fd);

    removeClientFromChannels(fd);

    clients.erase(fd);

    poll_fds.erase(
        poll_fds.begin() + index);
}

Client *Server::getClient(int fd)
{
    std::map<int, Client>::iterator it = clients.find(fd);
    if (it == clients.end())
        return NULL;
    return &(it->second);
}

const Client *Server::getClient(int fd) const
{
    std::map<int, Client>::const_iterator it = clients.find(fd);
    if (it == clients.end())
        return NULL;
    return &(it->second);
}

std::map<std::string, Channel> &Server::getChannels()
{
    return channels;
}

Channel *Server::findChannel(const std::string &name)
{
    std::map<std::string, Channel>::iterator it = channels.find(name);
    if (it == channels.end())
        return NULL;
    return &(it->second);
}

void Server::eraseChannel(const std::string &name)
{
    channels.erase(name);
}

int Server::getFdByNickname(const std::string &nickname) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin();
         it != clients.end();
         ++it)
    {
        if (it->second.getNickname() == nickname)
            return it->first;
    }
    return -1;
}

bool Server::isNicknameTaken(const std::string &nickname, int exceptFd) const
{
    for (std::map<int, Client>::const_iterator it = clients.begin();
         it != clients.end();
         ++it)
    {
        if (it->first != exceptFd && it->second.getNickname() == nickname)
            return true;
    }
    return false;
}

bool Server::isValidNickname(const std::string &nickname) const
{
    if (nickname.empty() || nickname.size() > 9)
        return false;
    if (!std::isalpha(static_cast<unsigned char>(nickname[0])) && nickname[0] != '_' && nickname[0] != '-')
        return false;
    for (size_t i = 1; i < nickname.size(); ++i)
    {
        unsigned char c = static_cast<unsigned char>(nickname[i]);
        if (!std::isalnum(c) && c != '_' && c != '-' && c != '[' && c != ']' && c != '{' && c != '}')
            return false;
    }
    return true;
}

std::string Server::getNickname(int fd) const
{
    const Client *client = getClient(fd);
    if (!client)
        return "*";
    if (client->getNickname().empty())
        return "*";
    return client->getNickname();
}

std::string Server::makePrefix(int fd) const
{
    const Client *client = getClient(fd);
    if (!client)
        return "unknown!unknown@localhost";

    std::string nick = client->getNickname().empty() ? "unknown" : client->getNickname();
    std::string user = client->getUsername().empty() ? "unknown" : client->getUsername();
    return nick + "!" + user + "@localhost";
}

void Server::broadcastToChannel(const std::string &channelName,
                                const std::string &message,
                                int excludeFd)
{
    Channel *channel = findChannel(channelName);
    if (!channel)
        return;

    const std::set<int> &members = channel->getMembers();
    for (std::set<int>::const_iterator it = members.begin();
         it != members.end();
         ++it)
    {
        if (*it == excludeFd)
            continue;
        sendMessage(*it, message);
    }
}

void Server::removeClientFromChannels(int fd)
{
    std::vector<std::string> emptyChannels;

    for (std::map<std::string, Channel>::iterator it = channels.begin();
         it != channels.end();
         ++it)
    {
        if (it->second.hasMember(fd, getNickname(fd)))
        {
            it->second.removeMember(fd, getNickname(fd));
            if (it->second.empty())
                emptyChannels.push_back(it->first);
        }
    }

    for (size_t i = 0; i < emptyChannels.size(); ++i)
        channels.erase(emptyChannels[i]);
}

void Server::broadcastQuit(int fd, const std::string &message)
{
    std::vector<std::string> channelsToClean;

    for (std::map<std::string, Channel>::iterator it = channels.begin();
         it != channels.end();
         ++it)
    {
        if (it->second.hasMember(fd, getNickname(fd)))
        {
            broadcastToChannel(it->first, message, -1);
            it->second.removeMember(fd, getNickname(fd));
            if (it->second.empty())
                channelsToClean.push_back(it->first);
        }
    }

    for (size_t i = 0; i < channelsToClean.size(); ++i)
        channels.erase(channelsToClean[i]);
}

void Server::disconnectClient(int fd)
{
    removeClientFromChannels(fd);

    close(fd);

    clients.erase(fd);

    for (size_t i = 0; i < poll_fds.size(); ++i)
    {
        if (poll_fds[i].fd == fd)
        {
            poll_fds.erase(poll_fds.begin() + i);
            break;
        }
    }
}