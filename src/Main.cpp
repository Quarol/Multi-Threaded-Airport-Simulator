#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <memory>

#include "Constants.hpp"
#include "Gate.hpp"
#include "PassengerFactory.hpp"
#include "Plane.hpp"
#include "Counter.hpp"

std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
auto passengerFactory = std::make_shared<PassengerFactory>();
bool wasTyped = false;
int numberOfPassengers = 0;
auto counter = std::make_shared<Counter>();

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

        passengerThreads.emplace_back(
            [gateid, passenger = std::move(passengers[i])]() mutable {
                gates[gateid].assignPassenger(passenger);
            });
    }

    for (auto& thread : passengerThreads) {
        thread.join();
    }
}

void userInput()
{
    while (true)
    {
        std::string input;
        std::cin >> input;

        if (input[0] == 'p') 
        {
            numberOfPassengers = std::stoi(input.substr(1, input.length() - 1));
            wasTyped = true;
        }

        if (input[0] == 'a') 
        {
            int numberOfPlanes = std::stoi(input.substr(1, input.length() - 1));
            for (auto& gate : gates) 
            {
                for (int i = 0; i < numberOfPlanes; ++i)
                    gate.addPlane();
            }
        }
    }
}

int main()
{
    int nextId = 0;
    for (auto& gate : gates)
        gate.setId(nextId++);

    for (auto& gate : gates) {
        gate = Gate(counter);
    }

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