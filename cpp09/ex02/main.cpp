#include "PmergeMe.hpp"
#include <ctime>
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <positive integers>" << std::endl;
        return 1;
    }

    PmergeVector vectorSorter;
    PmergeDeque dequeSorter;

    try
    {
        clock_t start = clock();
        vectorSorter.applyMergeInsertSort(argv);
        clock_t vectorTime = clock() - start;

        start = clock();
        dequeSorter.applyMergeInsertSort(argv);
        clock_t dequeTime = clock() - start;

        std::cout << "Before: ";
        vectorSorter.printBefore();

        std::cout << "\nAfter: ";
        vectorSorter.printAfter();

        std::cout << "\nTime to process a range of "
                  << argc - 1
                  << " elements with std::vector : "
                  << static_cast<double>(vectorTime) * 1000000 / CLOCKS_PER_SEC
                  << " us" << std::endl;

        std::cout << "Time to process a range of "
                  << argc - 1
                  << " elements with std::deque : "
                  << static_cast<double>(dequeTime) * 1000000 / CLOCKS_PER_SEC
                  << " us" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}