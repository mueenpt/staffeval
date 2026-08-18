#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>

class Client
{
private:
    int fd;

    std::string buffer;
    bool password_ok;
    std::string nickname;
    std::string username;
    bool registered;
public:
    Client();
    Client(int fd);

    int getFd() const;
    std::string &getBuffer();

    void appendBuffer(const std::string &data);

    void clearBuffer();
    bool isPasswordOk() const;
    void setPasswordOk(bool value);
    std::string getNickname() const;

    void setNickname(const std::string &nickname);

    std::string getUsername() const;

    void setUsername(const std::string &username);
    bool isRegistered() const;
    void setRegistered(bool value);
};

#endif