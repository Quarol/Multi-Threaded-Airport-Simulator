#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <memory>

#include "Constants.hpp"
#include "Gate.hpp"
#include "PassengerFactory.hpp"

std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
auto passengerFactory = std::make_shared<PassengerFactory>();
bool wasTyped = false;
int numberOfPassengers = 0;

int selectGateNumber(int i)
{
    int temp = numberOfPassengers * i;
    return i % gates.size();
}

void addPassengers(int numberOfPassengers)
{
    std::vector<Passenger> passengers = passengerFactory->createMultiplePassengersWithLogger(numberOfPassengers);

    // Assigning passengers to gates
    std::vector<std::thread> passengerThreads;
    for (int i = 0; i < passengers.size(); i++)
    {
        int gateid = selectGateNumber(i);

        std::thread(
            [gateid, passenger = std::move(passengers[i])]() mutable {
            gates[gateid].assignPassenger(passenger);
        }
        ).detach();

    }
}

void userInput()
{
    while (true)
    {
        std::string input;
        std::cin >> input;

        if (input[0] == 'p') {
            numberOfPassengers = std::stoi(input.substr(1, input.length()-1));
            wasTyped = true;
        }

        if (input[1] == 'a') {
            ;
        }
    }
}

int main()
{
    int nextId = 0;
    for (auto& gate : gates)
        gate.setId(nextId++);

    std::thread inputThread(userInput);

    while (true)
    {
        if (wasTyped)
        {
            wasTyped = false;
            std::thread(addPassengers, numberOfPassengers).detach();
        }
    }

    inputThread.join();

    return 0;
}