#include "PmergeMe.hpp"

PmergeMe::PmergeMe(const std::vector<size_t>& arr) : _vectorData(arr), _dequeData(arr.begin(), arr.end()) {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other) : _vectorData(other._vectorData), _dequeData(other._dequeData){}

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other) {}
    return *this;
}

void PmergeMe::sortwithVector()
{
    fordJohnsonSortVector(_vectorData);
}

void PmergeMe::sortwithDeque()
{
    fordJohnsonSortDeque(_dequeData);
}

void PmergeMe::fordJohnsonSortVector(std::vector<size_t> &arr)
{
    insertVector(arr, 0, arr.size() - 1);
}

void PmergeMe::fordJohnsonSortDeque(std::deque<size_t> &arr)
{
    insertDeque(arr, 0, arr.size() - 1);
}

const std::deque<size_t>& PmergeMe::getDequeData() const
{
    return _dequeData;
}

const std::vector<size_t>& PmergeMe::getVectorData() const
{
    return _vectorData;
}

const std::size_t PmergeMe::SequenceSize[33] = {
    0, 1, 1, 3, 5, 11, 21, 43, 85, 171, 341, 683, 1365, 2731, 5461, 
    10923, 21845, 43691, 87381, 174763, 349525, 699051, 1398101, 
    2796203, 5592405, 11184811, 22369621, 44739243, 89478485, 
    178956971, 357913941, 715827883, 1431655765};

std::vector<size_t> PmergeMe::generateJakobSequence(size_t n)
{
    //j[n] = 2 * j[n-1] + j[n-2]
    std::vector<size_t> jSeq;
    size_t j0 = 0;
    size_t j1 = 1;

    if (n == 0)
    {
        return jSeq;
    }
    else if (n == 1)
    {
        jSeq.push_back(j0);
        return jSeq;
    }
    else if (n == 2)
    {
        jSeq.push_back(j0);
        jSeq.push_back(j1);
        return jSeq;
    }
    else
    {
        jSeq.push_back(j0);
        jSeq.push_back(j1);
        for (size_t i = 2; i < n; i++)
        {
            size_t j = 2 * jSeq[i - 1] + jSeq[i - 2];
            jSeq.push_back(j);
        }
    }
    return jSeq;
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
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<size_t> jSeq = generateJakobSequence(arr.size());

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++)
    {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}