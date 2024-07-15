#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    std::vector<int> vec;
    std::deque<int> deq;

    for (int i = 1; i < argc; ++i) {
        int num;
        std::istringstream iss(argv[i]);
        if (!(iss >> num) || num <= 0) {
            std::cerr << "Error: Invalid input '" << argv[i] << "'." << std::endl;
            return 1;
        }
        vec.push_back(num);
        deq.push_back(num);
    }

    std::cout << "Before: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    PmergeMe pmergeMe;

    clock_t start_vec = clock();
    pmergeMe.mergeInsertSort(vec);
    clock_t end_vec = clock();
    double time_vec = static_cast<double>(end_vec - start_vec) / CLOCKS_PER_SEC * 1000000;

    clock_t start_deq = clock();
    pmergeMe.mergeInsertSort(deq);
    clock_t end_deq = clock();
    double time_deq = static_cast<double>(end_deq - start_deq) / CLOCKS_PER_SEC * 1000000;

    std::cout << "After: ";
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << vec.size() << " elements with std::vector: " << time_vec << " us" << std::endl;
    std::cout << "Time to process a range of " << deq.size() << " elements with std::deque: " << time_deq << " us" << std::endl;

    return 0;
}


