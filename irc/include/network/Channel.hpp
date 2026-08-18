#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <string>
#include <set>

class Channel
{
private:
    std::string name;
    std::string topic;
    std::string key;

    bool invite_only;
    bool topic_restricted;
    int user_limit;

    std::set<int> members;
    std::set<std::string> member_nicks;
    std::set<int> operators;
    std::set<int> invited;
    std::set<std::string> invited_nicks;

public:
    Channel();
    Channel(const std::string &name);

    const std::string &getName() const;

    const std::string &getTopic() const;
    void setTopic(const std::string &new_topic);

    bool isInviteOnly() const;
    void setInviteOnly(bool value);

    bool isTopicRestricted() const;
    void setTopicRestricted(bool value);

    bool hasKey() const;
    const std::string &getKey() const;
    void setKey(const std::string &new_key);
    void clearKey();

    bool hasUserLimit() const;
    int getUserLimit() const;
    void setUserLimit(int limit);
    void clearUserLimit();

    bool hasMember(int fd) const;
    bool hasMember(int fd, const std::string &nickname) const;
    void addMember(int fd, const std::string &nickname);
    void removeMember(int fd, const std::string &nickname);
    bool empty() const;

    bool isOperator(int fd) const;
    void addOperator(int fd);
    void removeOperator(int fd);

    bool isInvited(int fd, const std::string &nickname) const;
    void invite(int fd, const std::string &nickname);
    void revokeInvite(int fd, const std::string &nickname);

    size_t memberCount() const;
    const std::set<int> &getMembers() const;
};

#endif