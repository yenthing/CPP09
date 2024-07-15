#include "BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <input file>" << std::endl;
        return 1;
    }
    
    std::string inputFile = argv[1];
    if (!BitcoinExchange::isCSVFile(inputFile))
    {
        std::cerr << "Error: input file must be a .csv file." << std::endl;
        return 1;
    }

    try
    {
        BitcoinExchange exchange("data.csv");
        exchange.processFile(inputFile);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}
