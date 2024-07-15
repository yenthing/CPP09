#pragma once

#include <string>
#include <stack>
#include <stdexcept>
#include <iostream>
#include <sstream>

class RPN 
{  
    public:
        RPN();
        ~RPN();
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);

        int evaluate(const std::string& expression);

    private:
        bool whichOperator(const std::string& token);
        bool isValidNumber(const std::string& token);
        int startOperation(const std::string& operation, int operand1, int operand2);
};

