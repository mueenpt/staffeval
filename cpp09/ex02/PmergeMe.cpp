#include "PmergeMe.hpp"

void PmergeVector::createVectorPairs()
{
    int size = this->vec.size() / 2;
    unsigned int i = 0;

    while (size != 0)
    {
        this->vecPair.push_back(std::make_pair(this->vec.at(i),this->vec.at(i + 1)));
        i += 2;
        size--;
    }
}

void PmergeVector::sortVectorPairs()
{
    unsigned int i = 0;
    int tmp;

    while (i < this->vecPair.size())
    {
        if (this->vecPair.at(i).first < this->vecPair.at(i).second)
        {
            tmp = this->vecPair.at(i).first;
            this->vecPair.at(i).first = this->vecPair.at(i).second;
            this->vecPair.at(i).second = tmp;
        }
        i++;
    }
}

void PmergeVector::mergeSort(std::vector<std::pair<int, int> > &array,int begin,int end)
{
    int mid;

    if (begin >= end)
        return;

    mid = begin + (end - begin) / 2;

    this->mergeSort(array, begin, mid);
    this->mergeSort(array, mid + 1, end);
    this->merge(array, begin, mid, end);
}

void PmergeVector::merge(std::vector<std::pair<int, int> > &array,int begin,int mid,int end)
{
    size_t leftArrayIndex = 0;
    size_t rightArrayIndex = 0;
    size_t mergedArrayIndex = begin;

    std::vector<std::pair<int, int> > leftArray(array.begin() + begin,array.begin() + mid + 1);

    std::vector<std::pair<int, int> > rightArray(array.begin() + mid + 1,array.begin() + end + 1);

    while (leftArrayIndex < leftArray.size() && rightArrayIndex < rightArray.size())
    {
        if (leftArray[leftArrayIndex].first <= rightArray[rightArrayIndex].first)
        {
            array[mergedArrayIndex] = leftArray[leftArrayIndex];
            leftArrayIndex++;
        }
        else
        {
            array[mergedArrayIndex] = rightArray[rightArrayIndex];
            rightArrayIndex++;
        }
        mergedArrayIndex++;
    }

    while (leftArrayIndex < leftArray.size())
    {
        array[mergedArrayIndex] = leftArray[leftArrayIndex];
        leftArrayIndex++;
        mergedArrayIndex++;
    }

    while (rightArrayIndex < rightArray.size())
    {
        array[mergedArrayIndex] = rightArray[rightArrayIndex];
        rightArrayIndex++;
        mergedArrayIndex++;
    }
}

void PmergeVector::createMainChainAndPend()
{
    size_t i = 0;

    this->mainChain.push_back(this->vecPair.at(0).second);

    while (i < this->vecPair.size())
    {
        this->mainChain.push_back(this->vecPair.at(i).first);
        this->pend.push_back(this->vecPair.at(i).second);
        i++;
    }
}

void PmergeVector::insertToMainChain()
{
    this->generatPositions();

    size_t addedCount = 0;

    for (size_t i = 0; i < this->positions.size(); i++)
    {
        int target = this->pend.at(this->positions[i] - 1);

        size_t endPos = this->positions[i] + addedCount;

        size_t pos = this->binarySearch(this->mainChain,target,0,endPos);

        this->mainChain.insert(this->mainChain.begin() + pos, target);

        addedCount++;
    }

    if (this->vec.size() % 2 != 0)
    {
        int target = this->vec.at(this->vec.size() - 1);

        size_t pos = this->binarySearch(this->mainChain,target,0,this->mainChain.size() - 1);

        this->mainChain.insert(this->mainChain.begin() + pos, target);
    }
}

void PmergeVector::generatPositions()
{
    size_t val;
    size_t pos;
    size_t lastPos;
    size_t i;

    if (this->pend.empty())
        return;

    this->generateJacobInsertionSequence();

    lastPos = 1;
    val = 1;
    i = 0;

    while (i < this->jacobSequence.size())
    {
        val = this->jacobSequence.at(i);

        this->positions.push_back(val);

        pos = val - 1;
        while (pos > lastPos)
        {
            this->positions.push_back(pos);
            pos--;
        }

        lastPos = val;
        i++;
    }

    while (val++ < this->pend.size())
        this->positions.push_back(val);
}

void PmergeVector::generateJacobInsertionSequence()
{
    size_t size;
    size_t jacobIndex;
    int index;

    size = this->pend.size();
    index = 3;

    jacobIndex = this->jacobsthal(index);

    while (jacobIndex < size - 1)
    {
        this->jacobSequence.push_back(jacobIndex);

        index++;
        jacobIndex = this->jacobsthal(index);
    }
}

int PmergeVector::jacobsthal(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return this->jacobsthal(n - 1) + 2 * this->jacobsthal(n - 2);
}

int PmergeVector::binarySearch(std::vector<int> array,int target,int begin,int end)
{
    int mid;

    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;

        if (target == array.at(mid))
            return mid;

        if (target > array.at(mid))
            begin = mid + 1;
        else
            end = mid - 1;
    }

    if (target > array.at(mid))
        return mid + 1;
    else
        return mid;
}

void PmergeVector::getIntegerSequence(char *av[])
{
    int i = 1;
    char *ptr;
    int val;

    while (av[i])
    {
        if (av[i][0] == '\0')
            throw PmergeException();

        val = std::strtol(av[i], &ptr, 10);

        if (*ptr != '\0' || val < 0)
            throw PmergeException();

        this->vec.push_back(val);
        i++;
    }
}

void PmergeVector::applyMergeInsertSort(char *av[])
{
    this->getIntegerSequence(av);

    if (this->vec.size() == 1)
    {
        this->mainChain.push_back(this->vec.at(0));
        return;
    }

    this->createVectorPairs();
    this->sortVectorPairs();
    this->mergeSort(this->vecPair, 0, this->vecPair.size() - 1);
    this->createMainChainAndPend();
    this->insertToMainChain();
}

const std::vector<int> &PmergeVector::getMainChain() const
{
    return this->mainChain;
}

PmergeVector::PmergeVector()
{
}
PmergeVector::~PmergeVector()
{
}

void PmergeDeque::createDequePairs()
{
    int size = this->deque.size() / 2;
    unsigned int i = 0;

    while (size != 0)
    {
        this->dequePair.push_back(std::make_pair(this->deque.at(i),this->deque.at(i + 1)));
        i += 2;
        size--;
    }
}

void PmergeDeque::sortDequePairs()
{
    unsigned int i = 0;
    int tmp;

    while (i < this->dequePair.size())
    {
        if (this->dequePair.at(i).first < this->dequePair.at(i).second)
        {
            tmp = this->dequePair.at(i).first;
            this->dequePair.at(i).first = this->dequePair.at(i).second;
            this->dequePair.at(i).second = tmp;
        }
        i++;
    }
}

void PmergeDeque::mergeSort(std::deque<std::pair<int, int> > &array,int begin,int end)
{
    int mid;

    if (begin >= end)
        return;

    mid = begin + (end - begin) / 2;

    this->mergeSort(array, begin, mid);
    this->mergeSort(array, mid + 1, end);
    this->merge(array, begin, mid, end);
}

void PmergeDeque::merge(std::deque<std::pair<int, int> > &array,int begin,int mid,int end)
{
    size_t leftArrayIndex = 0;
    size_t rightArrayIndex = 0;
    size_t mergedArrayIndex = begin;

    std::deque<std::pair<int, int> > leftArray(array.begin() + begin,array.begin() + mid + 1);

    std::deque<std::pair<int, int> > rightArray(array.begin() + mid + 1,array.begin() + end + 1);

    while (leftArrayIndex < leftArray.size() && rightArrayIndex < rightArray.size())
    {
        if (leftArray[leftArrayIndex].first <= rightArray[rightArrayIndex].first)
        {
            array[mergedArrayIndex] = leftArray[leftArrayIndex];
            leftArrayIndex++;
        }
        else
        {
            array[mergedArrayIndex] = rightArray[rightArrayIndex];
            rightArrayIndex++;
        }
        mergedArrayIndex++;
    }

    while (leftArrayIndex < leftArray.size())
    {
        array[mergedArrayIndex] = leftArray[leftArrayIndex];
        leftArrayIndex++;
        mergedArrayIndex++;
    }

    while (rightArrayIndex < rightArray.size())
    {
        array[mergedArrayIndex] = rightArray[rightArrayIndex];
        rightArrayIndex++;
        mergedArrayIndex++;
    }
}

void PmergeDeque::createMainChainAndPend()
{
    size_t i = 0;

    this->mainChain.push_back(this->dequePair.at(0).second);

    while (i < this->dequePair.size())
    {
        this->mainChain.push_back(this->dequePair.at(i).first);
        this->pend.push_back(this->dequePair.at(i).second);
        i++;
    }
}

void PmergeDeque::insertToMainChain()
{
    this->generatPositions();

    size_t addedCount = 0;

    for (size_t i = 0; i < this->positions.size(); i++)
    {
        int target = this->pend.at(this->positions[i] - 1);

        size_t endPos = this->positions[i] + addedCount;

        size_t pos = this->binarySearch(this->mainChain,target,0,endPos);

        this->mainChain.insert(this->mainChain.begin() + pos, target);

        addedCount++;
    }

    if (this->deque.size() % 2 != 0)
    {
        int target = this->deque.at(this->deque.size() - 1);

        size_t pos = this->binarySearch(this->mainChain,target,0,this->mainChain.size() - 1);

        this->mainChain.insert(this->mainChain.begin() + pos, target);
    }
}

void PmergeDeque::generatPositions()
{
    size_t val;
    size_t pos;
    size_t lastPos;
    size_t i;

    if (this->pend.empty())
        return;

    this->generateJacobInsertionSequence();

    lastPos = 1;
    val = 1;
    i = 0;

    while (i < this->jacobSequence.size())
    {
        val = this->jacobSequence.at(i);

        this->positions.push_back(val);

        pos = val - 1;
        while (pos > lastPos)
        {
            this->positions.push_back(pos);
            pos--;
        }

        lastPos = val;
        i++;
    }

    while (val++ < this->pend.size())
        this->positions.push_back(val);
}

void PmergeDeque::generateJacobInsertionSequence()
{
    size_t size;
    size_t jacobIndex;
    int index;

    size = this->pend.size();
    index = 3;

    jacobIndex = this->jacobsthal(index);

    while (jacobIndex < size - 1)
    {
        this->jacobSequence.push_back(jacobIndex);

        index++;
        jacobIndex = this->jacobsthal(index);
    }
}

int PmergeDeque::jacobsthal(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return this->jacobsthal(n - 1) + 2 * this->jacobsthal(n - 2);
}

int PmergeDeque::binarySearch(std::deque<int> array,int target,int begin,int end)
{
    int mid;

    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;

        if (target == array.at(mid))
            return mid;

        if (target > array.at(mid))
            begin = mid + 1;
        else
            end = mid - 1;
    }

    if (target > array.at(mid))
        return mid + 1;
    else
        return mid;
}

void PmergeDeque::getIntegerSequence(char *av[])
{
    int i = 1;
    char *ptr;
    int val;

    while (av[i])
    {
        if (av[i][0] == '\0')
            throw PmergeException();

        val = std::strtol(av[i], &ptr, 10);

        if (*ptr != '\0' || val < 0)
            throw PmergeException();

        this->deque.push_back(val);
        i++;
    }
}

void PmergeDeque::applyMergeInsertSort(char *av[])
{
    this->getIntegerSequence(av);

    if (this->deque.size() == 1)
    {
        this->mainChain.push_back(this->deque.at(0));
        return;
    }

    this->createDequePairs();
    this->sortDequePairs();
    this->mergeSort(this->dequePair, 0, this->dequePair.size() - 1);
    this->createMainChainAndPend();
    this->insertToMainChain();
}

PmergeDeque::PmergeDeque()
{
}

PmergeDeque::~PmergeDeque()
{
}

void PmergeVector::printBefore()
{
    for (size_t i = 0; i < this->vec.size(); i++)
        std::cout << this->vec.at(i) << " ";
}

void PmergeVector::printAfter()
{
    for (size_t i = 0; i < this->mainChain.size(); i++)
        std::cout << this->mainChain.at(i) << " ";
}


PmergeException::PmergeException()
{
}

PmergeException::~PmergeException() throw()
{
}

const char *PmergeException::what() const throw()
{
    return "Error";
}

