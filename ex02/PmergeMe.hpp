#pragma once

#include <string>
#include <vector>
#include <deque>
#include <stdexcept>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cmath>

class PmergeMe
{  
    public:
        PmergeMe(const std::vector<size_t>& arr);
        ~PmergeMe();
        PmergeMe(const PmergeMe& other);
        PmergeMe& operator=(const PmergeMe& other);

        void sortwithVector();
        void sortwithDeque();

        const std::vector<size_t>& getVectorData() const;
        const std::deque<size_t>& getDequeData() const;

    private:
        std::vector<size_t> _vectorData;
        std::deque<size_t> _dequeData;

        void fordJohnsonSortVector(std::vector<size_t> &arr);
        void fordJohnsonSortDeque(std::deque<size_t> &arr);
        
        void insertVector(std::vector<size_t> &arr, int left, int right);
        void insertDeque(std::deque<size_t> &arr, int left, int right);
        
        void mergeVector(std::vector<size_t> &arr, int left, int mid, int right);
        void mergeDeque(std::deque<size_t> &arr, int left, int mid, int right);
        
        static const std::size_t SequenceSize[33];
        static std::vector<size_t> generateJakobSequence(size_t n);
};
