#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>
#include <stdexcept>

class RPN
{
private:
    std::stack<int> _stack;

public:
    RPN();
    ~RPN();

    void evaluate(const std::string &expression);
};

#endif