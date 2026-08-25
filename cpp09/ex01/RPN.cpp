#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

static bool isOperator(const std::string &token)
{
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

static int applyOperation(int a, int b, const std::string &op)
{
    if (op == "+")
        return a + b;
    if (op == "-")
        return a - b;
    if (op == "*")
        return a * b;
    if (op == "/")
    {
        if (b == 0)
            throw std::runtime_error("Error");
        return a / b;
    }
    throw std::runtime_error("Error");
}

void RPN::evaluate(const std::string &expression)
{
    while (!_stack.empty())
    _stack.pop();
    
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token)
    {
        if (token.length() == 1 && isdigit(token[0]))
        {
            _stack.push(token[0] - '0');
        }
        else if (isOperator(token))
        {
            if (_stack.size() < 2)
                throw std::runtime_error("Error");

            int b = _stack.top();
            _stack.pop();
            int a = _stack.top();
            _stack.pop();

            int result = applyOperation(a, b, token);
            _stack.push(result);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }

    if (_stack.size() != 1)
        throw std::runtime_error("Error");

    std::cout << _stack.top() << std::endl;
}