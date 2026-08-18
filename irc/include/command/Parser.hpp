#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <vector>

namespace Parser
{
    std::string trim(const std::string &s);
    std::vector<std::string> splitSpaces(const std::string &s);
    std::string toUpper(std::string s);
    std::string takeTrailingMessage(const std::string &line);
    bool isValidChannelName(const std::string &name);
    bool isValidNickname(const std::string &nick);
}

#endif