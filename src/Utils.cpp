#include "Utils.hpp"

#include <random>
#include <string>

std::string Utils::addBrackets(const std::string& str)
{
    return "[" + str + "]";
}

std::string Utils::addBrackets(int number)
{
    return addBrackets(std::to_string(number));
}