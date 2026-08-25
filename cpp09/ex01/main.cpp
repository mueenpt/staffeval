#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "./RPN <mathamatical expression>" << std::endl;
        return 1;
    }

    try
    {
        RPN rpn;
        rpn.evaluate(argv[1]);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    return 0;
}