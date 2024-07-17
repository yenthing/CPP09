#pragma once

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdio>

class BitcoinExchange
{
    public:
        BitcoinExchange();
        BitcoinExchange(const std::string& dbFile);
        ~BitcoinExchange();
        BitcoinExchange &operator=(const BitcoinExchange &src);

        static bool isCSVFile(const std::string& filename);
        float getRate(const std::string& date) const;
        bool isValidDate(const std::string& date) const;
        bool isValidValue(const std::string& valueStr, float& value) const;
        void processFile(const std::string& filename) const;

    private:
        std::map<std::string, float> rates; //store exchange rates
        bool loadDatabase(const std::string& dbFile);
};