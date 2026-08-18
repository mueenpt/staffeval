#include "Client.hpp"
#include <string>
Client::Client()
    : fd(-1),
      password_ok(false),
      registered(false)
{
}

Client::Client(int fd)
    : fd(fd),
      password_ok(false),
      registered(false)
{
}

int Client::getFd() const
{
    return fd;
}

std::string &Client::getBuffer()
{
    return buffer;
}

void Client::appendBuffer(const std::string &data)
{
    buffer += data;
}

void Client::clearBuffer()
{
    buffer.clear();
}
bool Client::isPasswordOk() const
{
    return password_ok;
}

void Client::setPasswordOk(bool value)
{
    password_ok = value;
}

std::string Client::getNickname() const
{
    return nickname;
}

void Client::setNickname(const std::string &nickname)
{
    this->nickname = nickname;
}

std::string Client::getUsername() const
{
    return username;
}

void Client::setUsername(const std::string &username)
{
    this->username = username;
}
bool Client::isRegistered() const
{
    return registered;
}

void Client::setRegistered(bool value)
{
    registered = value;
}