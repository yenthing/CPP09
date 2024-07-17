#pragma once

#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <utility>

class PmergeMe
{  
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        void fordJohnsonSortVector(std::vector<size_t> &arr);
        void fordJohnsonSortDeque(std::deque<size_t> &arr);

    private:
        
        void insertVector(std::vector<size_t> &arr, int left, int right);
        void insertDeque(std::deque<size_t> &arr, int left, int right);
        
        void mergeVector(std::vector<size_t> &arr, int left, int mid, int right);
        void mergeDeque(std::deque<size_t> &arr, int left, int mid, int right);
        
        static const std::size_t SequenceSize[33];
        static std::pair<size_t, size_t> makePairs(std::size_t n);
        static std::vector<size_t> setJakobSeqV(size_t n);
        static std::deque<size_t> setJakobSeqD(size_t n);
};
