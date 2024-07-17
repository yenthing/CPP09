#include "PmergeMe.hpp"
#include <utility>

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}
PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other) 
    {}
    return *this;
}

const std::size_t PmergeMe::SequenceSize[33] = {
    0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 
    10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 
    2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 
    178956971, 357913941, 715827883, 1431655765};

std::pair<size_t, size_t> PmergeMe::makePairs(std::size_t n)
{
    if (n < 2)
    {
        throw std::invalid_argument("n must be greater than 1");
    }
    for (size_t i = 1; i < 33; i++)
    {
        if (n < SequenceSize[i])
            return std::make_pair(SequenceSize[i - 1], SequenceSize[i]);
    }

    throw std::out_of_range("n is too large to find a pair in SequenceSize array");
}

std::vector<size_t> PmergeMe::setJakobSeqV(size_t n)
{
    if (n < 2)
    {
        throw std::invalid_argument("n must be greater than 1");
    }

    std::vector<size_t> jSeq;
    std::pair<size_t, size_t> pair = makePairs(n);
    if (pair.first > pair.second)
    {
        std::swap(pair.first, pair.second);
    }

    for (size_t i = 0; i < pair.second; i++)
    {
        jSeq.push_back(i);
    }

    return jSeq;
}

std::deque<size_t> PmergeMe::setJakobSeqD(size_t n)
{
    if (n < 2)
    {
        throw std::invalid_argument("n must be greater than 1");
    }

    std::deque<size_t> jSeq;
    std::pair<size_t, size_t> pair = makePairs(n);
    if (pair.first > pair.second)
    {
        std::swap(pair.first, pair.second);
    }

    for (size_t i = 0; i < pair.second; i++)
    {
        jSeq.push_back(i);
    }

    return jSeq;
}

void PmergeMe::fordJohnsonSortVector(std::vector<size_t> &arr)
{
    if (arr.size() < 2)
        return;
    insertVector(arr, 0, arr.size() - 1);
}

void PmergeMe::fordJohnsonSortDeque(std::deque<size_t> &arr)
{
    if (arr.size() < 2)
        return;
    insertDeque(arr, 0, arr.size() - 1);
}

void PmergeMe::insertVector(std::vector<size_t> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        insertVector(arr, left, mid);
        insertVector(arr, mid + 1, right);
        mergeVector(arr, left, mid, right);
    }
}

void PmergeMe::insertDeque(std::deque<size_t> &arr, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        insertDeque(arr, left, mid);
        insertDeque(arr, mid + 1, right);
        mergeDeque(arr, left, mid, right);
    }
}

void PmergeMe::mergeVector(std::vector<size_t> &arr, int left, int mid, int right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    std::vector<size_t> L(arr.begin() + left, arr.begin() + mid + 1);
    std::vector<size_t> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    std::vector<size_t> jakobSeq = setJakobSeqV(n1 + n2);
    size_t idx = 0;

    size_t i = 0, j = 0;
    size_t k = left; // Start merging from the original 'left' index

    while (i < n1 && j < n2)
    {
        size_t a = jakobSeq[idx++];
        size_t b = jakobSeq[idx++];

        for (size_t count = a; count <= b; ++count)
        {
            if (i < n1 && j < n2)
            {
                if (L[i] <= R[j])
                {
                    arr[k++] = L[i++];
                }
                else
                {
                    arr[k++] = R[j++];
                }
            }
            else if (i < n1)
            {
                arr[k++] = L[i++];
            }
            else if (j < n2)
            {
                arr[k++] = R[j++];
            }
        }
    }

    // Copy remaining elements of L and R if any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}

void PmergeMe::mergeDeque(std::deque<size_t> &arr, int left, int mid, int right)
{
    size_t n1 = mid - left + 1;
    size_t n2 = right - mid;

    std::deque<size_t> L(arr.begin() + left, arr.begin() + mid + 1);
    std::deque<size_t> R(arr.begin() + mid + 1, arr.begin() + right + 1);

    std::deque<size_t> jakobSeq = setJakobSeqD(n1 + n2);
    size_t idx = 0;

    size_t i = 0, j = 0;
    size_t k = left; // Start merging from the original 'left' index

    while (i < n1 && j < n2)
    {
        size_t a = jakobSeq[idx++];
        size_t b = jakobSeq[idx++];

        for (size_t count = a; count <= b; ++count)
        {
            if (i < n1 && j < n2)
            {
                if (L[i] <= R[j])
                {
                    arr[k++] = L[i++];
                }
                else
                {
                    arr[k++] = R[j++];
                }
            }
            else if (i < n1)
            {
                arr[k++] = L[i++];
            }
            else if (j < n2)
            {
                arr[k++] = R[j++];
            }
        }
    }

    // Copy remaining elements of L and R if any
    while (i < n1)
    {
        arr[k++] = L[i++];
    }
    while (j < n2)
    {
        arr[k++] = R[j++];
    }
}
