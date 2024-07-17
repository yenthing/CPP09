#include "RPN.hpp"

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <RPN expression>" << std::endl;
        return 1;
    }

    std::string expression = argv[1];
    RPN rpn;

    try
    {
        double result = rpn.evaluate(expression);
        std::cout << result << std::endl;
    } 
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
