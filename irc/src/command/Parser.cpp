#include "Parser.hpp"

#include <sstream>
#include <cctype>

namespace Parser
{
    std::string trim(const std::string &s)
    {
        size_t start = 0;
        while (start < s.size() && (s[start] == ' ' || s[start] == '\t'))
            ++start;

        size_t end = s.size();
        while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
            --end;

        return s.substr(start, end - start);
    }

    std::vector<std::string> splitSpaces(const std::string &s)
    {
        std::vector<std::string> out;
        std::istringstream iss(s);
        std::string token;
        while (iss >> token)
            out.push_back(token);
        return out;
    }

    std::string toUpper(std::string s)
    {
        for (size_t i = 0; i < s.size(); ++i)
            s[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(s[i])));
        return s;
    }

    std::string takeTrailingMessage(const std::string &line)
    {
        size_t colon = line.find(" :");
        if (colon == std::string::npos)
            return "";
        return line.substr(colon + 2);
    }

    bool isValidChannelName(const std::string &name)
    {
        return !name.empty() && name[0] == '#';
    }

    bool isValidNickname(const std::string &nick)
    {
        if (nick.empty() || nick.size() > 9)
            return false;
        if (!std::isalpha(static_cast<unsigned char>(nick[0])) && nick[0] != '_' && nick[0] != '-')
            return false;
        for (size_t i = 1; i < nick.size(); ++i)
        {
            unsigned char c = static_cast<unsigned char>(nick[i]);
            if (!std::isalnum(c) && c != '_' && c != '-' && c != '[' && c != ']' && c != '{' && c != '}')
                return false;
        }
        return true;
    }
}
