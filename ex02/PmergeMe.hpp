#pragma once

#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

class PmergeMe
{  
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        void mergeInsertSort(std::vector<int> &arr);
        void mergeInsertSort(std::deque<int> &arr);

    private:
        void mergeInsertSortVector(std::vector<int> &arr, int left, int right);
        void mergeInsertSortDeque(std::deque<int> &arr, int left, int right);
        void mergeVector(std::vector<int> &arr, int left, int mid, int right);
        void mergeDeque(std::deque<int> &arr, int left, int mid, int right);
};

#
