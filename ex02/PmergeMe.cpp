#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}

PmergeMe::~PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other) {}
    return *this;
}

void PmergeMe::mergeInsertSort(std::vector<int> &arr)
{
    mergeInsertSortVector(arr, 0, arr.size() - 1);
}

void PmergeMe::mergeInsertSort(std::deque<int> &arr)
{
    mergeInsertSortDeque(arr, 0, arr.size() - 1);
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &arr, int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeInsertSortVector(arr, left, mid);
        mergeInsertSortVector(arr, mid + 1, right);
        mergeVector(arr, left, mid, right);
    }
}

void PmergeMe::mergeInsertSortDeque(std::deque<int> &arr, int left, int right)
{
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeInsertSortDeque(arr, left, mid);
        mergeInsertSortDeque(arr, mid + 1, right);
        mergeDeque(arr, left, mid, right);
    }
}

void PmergeMe::mergeVector(std::vector<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void PmergeMe::mergeDeque(std::deque<int> &arr, int left, int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;
    std::deque<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        } else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}
