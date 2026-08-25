#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <utility>
#include <exception>
#include <cstdlib>
#include <algorithm>

class PmergeException : public std::exception
{
public:
    PmergeException();
    virtual ~PmergeException() throw();
    virtual const char *what() const throw();
};

class PmergeVector
{
private:
    std::vector<int> vec;
    std::vector<int> positions;
    std::vector<std::pair<int, int> > vecPair;
    std::vector<int> mainChain;
    std::vector<int> pend;
    std::vector<int> jacobSequence;

    void getIntegerSequence(char *av[]);
    void createVectorPairs();
    void sortVectorPairs();
    

    void merge(std::vector<std::pair<int, int> > &array,
               int begin, int mid, int end);
    void mergeSort(std::vector<std::pair<int, int> > &array,
                   int begin, int end);

    void createMainChainAndPend();

    int binarySearch(std::vector<int> array, int target, int begin, int end);

    void generateJacobInsertionSequence();
    int jacobsthal(int n);
    void generatPositions();
    void insertToMainChain();

public:
    PmergeVector();
    ~PmergeVector();
    const std::vector<int> &getMainChain() const;
    void applyMergeInsertSort(char *av[]);
    void printBefore();
    void printAfter();
};

class PmergeDeque
{
private:
    std::deque<int> deque;
    std::deque<int> positions;
    std::deque<std::pair<int, int> > dequePair;
    std::deque<int> mainChain;
    std::deque<int> pend;
    std::deque<int> jacobSequence;

    void getIntegerSequence(char *av[]);
    void createDequePairs();
    void sortDequePairs();

    void merge(std::deque<std::pair<int, int> > &array,
               int begin, int mid, int end);
    void mergeSort(std::deque<std::pair<int, int> > &array,
                   int begin, int end);

    void createMainChainAndPend();

    int binarySearch(std::deque<int> array,
                     int target,
                     int begin,
                     int end);

    void generateJacobInsertionSequence();
    int jacobsthal(int n);
    void generatPositions();
    void insertToMainChain();

public:
    PmergeDeque();
    ~PmergeDeque();

    void applyMergeInsertSort(char *av[]);
};

#endif