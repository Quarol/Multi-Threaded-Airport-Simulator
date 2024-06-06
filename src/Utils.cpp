#include "Utils.hpp"

#include <random>
#include <string>

int Utils::generateRandomNumber() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int random_number = dis(gen);
    return random_number;
}

std::string Utils::addBrackets(const std::string& str)
{
    return "[" + str + "]";
}

std::string Utils::addBrackets(int number)
{
    return addBrackets(std::to_string(number));
}