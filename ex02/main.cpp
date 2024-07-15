#include "PmergeMe.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <ctime>

void printSequence(const std::string& prefix, const std::vector<int>& data)
{
    std::cout << prefix;
    for (size_t i = 0; i < data.size(); ++i)
    {
        std::cout << data[i];
        if (i != data.size() - 1)
        {
            std::cout << " ";
        }
    }
    std::cout << std::endl << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "Error: No input provided." << std::endl;
        return 1;
    }

    std::vector<int> data;
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
            data.push_back(num);
        }
        catch (const std::exception& e)
        {
            std::cerr << "Error: Invalid input '" << argv[i] << "'." << std::endl;
            return 1;
        }
    }



    std::cout << "Before: ";
    for (std::vector<int>::iterator it = data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    PmergeMe sorter(data);

    clock_t start = clock();
    sorter.sortwithVector();
    clock_t end = clock();
    double vectorSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;


    std::cout << "After (std::vector): ";
    const std::vector<int>& vectorResult = sorter.getVectorData();
    for (std::vector<int>::const_iterator it = vectorResult.begin(); it != vectorResult.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    std::cout << "Time to process a range of " << data.size() << " elements with std::vector: " 
              << vectorSortTime << " us" << std::endl << '\n';

    start = clock();
    sorter.sortwithDeque();
    end = clock();
    double dequeSortTime = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;

    //std::cout << "After (deque): ";
    // const std::deque<int>& dequeResult = sorter.getDequeResult();
    // for (std::deque<int>::const_iterator it = dequeResult.begin(); it != dequeResult.end(); ++it) {
        // std::cout << *it << " ";
    // }
    // std::cout << std::endl << std::endl;

    std::cout << "Time to process a range of " << data.size() << " elements with std::deque: " 
              << dequeSortTime << " us" << std::endl;

    return 0;
}


