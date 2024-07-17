#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <sstream>

void printVector(const std::vector<size_t>& vec)
{
    for (std::vector<size_t>::const_iterator it = vec.begin(); it != vec.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

void printDeque(const std::deque<size_t>& deq)
{
    for (std::deque<size_t>::const_iterator it = deq.begin(); it != deq.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    std::vector<size_t> vectorData;
    std::deque<size_t> dequeData;

    for (int i = 1; i < argc; ++i)
    {
        try
        {
            int num;
            std::istringstream iss(argv[i]);
            if (!(iss >> num) || num < 0)
            {
                throw std::invalid_argument("Non-positive integer.");
            }
            vectorData.push_back(num);
            dequeData.push_back(num);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: Invalid input '" << argv[i] << "'." << std::endl;
            return 1;
        }
    }
    
    std::cout << "Before: ";
    printVector(vectorData);
    std::cout << std::endl;

    PmergeMe pmerge;

    clock_t start = clock();
    pmerge.fordJohnsonSortVector(vectorData);
    clock_t end = clock();
    double vectorSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    // std::cout << "After (std::vector): ";
    // printVector(vectorData);
    // std::cout << std::endl;

    std::cout << "Time to process a range of " << vectorData.size() << " elements with std::vector: " 
              << vectorSortTime << " us" << std::endl << std::endl;

    start = clock();
    pmerge.fordJohnsonSortDeque(dequeData);
    end = clock();
    double dequeSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "After (deque): ";
    printDeque(dequeData);
    std::cout << std::endl;

    std::cout << "Time to process a range of " << dequeData.size() << " elements with std::deque: " 
              << dequeSortTime << " us" << std::endl;

    return 0;
}
