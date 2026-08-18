#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <poll.h>
#include <map>

#include "Client.hpp"
#include "Channel.hpp"

class Server
{
private:
    int server_fd;

    int port;
    std::string password;

    std::vector<pollfd> poll_fds;
    std::map<int, Client> clients;
    std::map<std::string, Channel> channels;

public:
    Server(int port, const std::string &password);
    ~Server();

    const std::string &getPassword() const;

    void setupSocket();
    void run();
    void handleCommand(int fd, const std::string &command);
    void checkRegistration(int fd);
    void sendMessage(int fd, const std::string &message);
    void removeClient(size_t index);

    Client *getClient(int fd);
    const Client *getClient(int fd) const;

    std::map<std::string, Channel> &getChannels();
    Channel *findChannel(const std::string &name);
    void eraseChannel(const std::string &name);

    int getFdByNickname(const std::string &nickname) const;
    bool isNicknameTaken(const std::string &nickname, int exceptFd) const;
    bool isValidNickname(const std::string &nickname) const;
    std::string getNickname(int fd) const;
    std::string makePrefix(int fd) const;

    void broadcastToChannel(const std::string &channelName,
                            const std::string &message,
                            int excludeFd);
    void removeClientFromChannels(int fd);

    void broadcastQuit(int fd, const std::string &message);
    void disconnectClient(int fd);
};

#endif