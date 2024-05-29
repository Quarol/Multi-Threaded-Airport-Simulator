#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <memory>

#include "Constants.hpp"
#include "Gate.hpp"
#include "PassengerFactory.hpp"

int main()
{
    std::cout << "test3";
    std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
    int nextId = 0;
    for (auto& gate : gates)
        gate.setId(nextId++);

    auto passengerFactory = std::make_shared<PassengerFactory>();

    std::vector<Passenger> passengers = passengerFactory->createMultiplePassengers(Constants::NUMBERS_OF_PASSENGERS);

    // Assining passengers to gates
    std::vector<std::thread> passengerThreads;
    for (int i = 0; i < passengers.size(); i++)
    {
        int gateId = i % gates.size();
        passengerThreads.emplace_back(
            [gateId, i, &gates, &passengers]()
            {
                gates[gateId].assignPassenger(passengers[i]);
            });
    }

    // Waiting for passenger threads to end
    for (auto& passengerThread : passengerThreads)
        passengerThread.join();

    return 0;
}