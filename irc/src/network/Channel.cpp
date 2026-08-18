#include "Channel.hpp"

Channel::Channel()
    : invite_only(false),
      topic_restricted(false),
      user_limit(-1)
{
}

Channel::Channel(const std::string &name)
    : name(name),
      invite_only(false),
      topic_restricted(false),
      user_limit(-1)
{
}

const std::string &Channel::getName() const
{
    return name;
}

const std::string &Channel::getTopic() const
{
    return topic;
}

void Channel::setTopic(const std::string &new_topic)
{
    topic = new_topic;
}

bool Channel::isInviteOnly() const
{
    return invite_only;
}

void Channel::setInviteOnly(bool value)
{
    invite_only = value;
}

bool Channel::isTopicRestricted() const
{
    return topic_restricted;
}

void Channel::setTopicRestricted(bool value)
{
    topic_restricted = value;
}

bool Channel::hasKey() const
{
    return !key.empty();
}

const std::string &Channel::getKey() const
{
    return key;
}

void Channel::setKey(const std::string &new_key)
{
    key = new_key;
}

void Channel::clearKey()
{
    key.clear();
}

bool Channel::hasUserLimit() const
{
    return user_limit >= 0;
}

int Channel::getUserLimit() const
{
    return user_limit;
}

void Channel::setUserLimit(int limit)
{
    user_limit = limit;
}

void Channel::clearUserLimit()
{
    user_limit = -1;
}

bool Channel::hasMember(int fd) const
{
    return members.find(fd) != members.end();
}

bool Channel::hasMember(int fd, const std::string &nickname) const
{
    return members.find(fd) != members.end()
        || member_nicks.find(nickname) != member_nicks.end();
}

void Channel::addMember(int fd, const std::string &nickname)
{
    members.insert(fd);
    if (!nickname.empty())
        member_nicks.insert(nickname);
}

void Channel::removeMember(int fd, const std::string &nickname)
{
    members.erase(fd);
    if (!nickname.empty())
        member_nicks.erase(nickname);
    operators.erase(fd);
    invited.erase(fd);
    if (!nickname.empty())
        invited_nicks.erase(nickname);
}

bool Channel::empty() const
{
    return members.empty();
}

bool Channel::isOperator(int fd) const
{
    return operators.find(fd) != operators.end();
}

void Channel::addOperator(int fd)
{
    operators.insert(fd);
}

void Channel::removeOperator(int fd)
{
    operators.erase(fd);
}

bool Channel::isInvited(int fd, const std::string &nickname) const
{
    return invited.find(fd) != invited.end()
        || invited_nicks.find(nickname) != invited_nicks.end();
}

void Channel::invite(int fd, const std::string &nickname)
{
    invited.insert(fd);
    if (!nickname.empty())
        invited_nicks.insert(nickname);
}

void Channel::revokeInvite(int fd, const std::string &nickname)
{
    invited.erase(fd);
    if (!nickname.empty())
        invited_nicks.erase(nickname);
}

size_t Channel::memberCount() const
{
    return members.size();
}

const std::set<int> &Channel::getMembers() const
{
    return members;
}
