#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const std::string& dbFile)
{
    loadDatabase(dbFile);
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &src)
{
    if (this == &src)
        return *this;
    rates = src.rates;
    return *this;
}

bool BitcoinExchange::isCSVFile(const std::string& filename)
{
    return filename.size() > 4 && filename.substr(filename.size() - 4) == ".csv";
}

void BitcoinExchange::loadDatabase(const std::string& dbFile)
{
    std::ifstream file(dbFile.c_str());
    if (!file) {
        std::cerr << "Error: could not open DATA file." << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, rateStr;
        if (std::getline(ss, date, ',') && std::getline(ss, rateStr))
        {
            std::istringstream rateStream(rateStr);
            double rate;
            rateStream >> rate;
            if (!rateStream.fail() && rateStream.eof())
                rates[date] = rate;
        }
    }
}

float BitcoinExchange::getRate(const std::string& date) const
{
    std::map<std::string, float>::const_iterator it = rates.lower_bound(date);
    if (it == rates.end() || it->first != date)
    {
        if (it == rates.begin()) 
            return 0.0;
        --it;
    }
    return it->second;
}

bool BitcoinExchange::isValidDate(const std::string& date) const 
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    int year, month, day;
    if (sscanf(date.c_str(), "%d-%d-%d", &year, &month, &day) != 3)
        return false;
    if (month < 1 || month > 12 || day < 1 || day > 31)
        return false;

    return true;
}

bool BitcoinExchange::isValidValue(const std::string& valueStr, float& value) const
{
    std::istringstream valueStream(valueStr);
    valueStream >> value;
    return !(valueStream.fail() || !valueStream.eof());
}

void trim(std::string& str)
{
    size_t start = str.find_first_not_of(" \t");
    size_t end = str.find_last_not_of(" \t");
    str = (start == std::string::npos || end == std::string::npos) ? "" : str.substr(start, end - start + 1);
}

void BitcoinExchange::processFile(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (!file)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream ss(line);
        std::string date, valueStr;
        if (line == "date | value")
            continue;
        else if (std::getline(ss, date, '|') && std::getline(ss, valueStr))
        {
            trim(date);
            trim(valueStr);

            if (!isValidDate(date))
            {
                std::cerr << "Error: bad input => " << date << std::endl;
                continue;
            }

            float value;
            if (!isValidValue(valueStr, value))
            {
                std::cerr << "Error: not a valid number." << std::endl;
                continue;
            }

            if (value < 0)
            {
                std::cerr << "Error: not a positive number." << std::endl;
                continue;
            }

            if (value > 1000)
            {
                std::cerr << "Error: too large a number." << std::endl;
                continue;
            }

            float rate = getRate(date);
            std::cout << date << " => " << value << " = " << (value * rate) << std::endl;
        }
        else
        {
            std::cerr << "Error: bad input format => " << line << std::endl;
        }
    }
}
