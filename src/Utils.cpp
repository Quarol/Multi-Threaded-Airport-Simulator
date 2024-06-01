#include "Utils.hpp"
#include <random>

int Utils::generate_random_number() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);

    int random_number = dis(gen);
    return random_number;
}