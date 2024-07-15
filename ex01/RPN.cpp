#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

RPN::RPN(const RPN &other)
{
    *this = other;
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
    {
       // Perform deep copy of members from other to this
        // Example: this->member = other.member;
    }
    return *this;
}

bool RPN::whichOperator(const std::string& token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

int RPN::startOperation(const std::string& operation, int operand1, int operand2)
{
    if (operation == "+") 
        return operand1 + operand2;
    if (operation == "-")
        return operand1 - operand2;
    if (operation == "*") 
        return operand1 * operand2;
    if (operation == "/")
    {
        if (operand2 == 0) 
            throw std::runtime_error("Division by zero");
        return operand1 / operand2;
    }
    throw std::runtime_error("Invalid operation");
}

bool RPN::isValidNumber(const std::string& token)
{
    if ((!isdigit(token[0]) && !(token[0] == '-' && isdigit(token[1]))) || token.size() != 1)
        return false;
    int number = token[0] - '0';
    return number >= 0 && number < 10;
}

int RPN::evaluate(const std::string& expression)
{
    std::stack<int> stk;
    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (isValidNumber(token))
        {
            stk.push(token[0] - '0');
        }
        else if (whichOperator(token))
        {
            if (stk.size() < 2)
                throw std::runtime_error("Insufficient operands");
            int operand2 = stk.top(); stk.pop();
            int operand1 = stk.top(); stk.pop();
            int result = startOperation(token, operand1, operand2);
            stk.push(result);
        }
        else
        {
            throw std::runtime_error("Invalid token");
        }
    }

    if (stk.size() != 1) 
        throw std::runtime_error("Invalid expression");

    return stk.top();
}
