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
#include "Runway.hpp"

std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
auto runway = std::make_shared<Runway>(1);
auto passengerFactory = std::make_shared<PassengerFactory>();

int selectGateNumber(int i)
{
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
            [gateid, passenger = std::move(passengers[i])]
            () mutable 
            {
                gates[gateid].assignPassenger(passenger);
            });
    }

    for (auto& thread : passengerThreads) 
    {
        thread.join();
    }
}

void addPlanes(int numberOfPlanes) 
{
    std::vector<Plane> planes;

    for (int i = 0; i < numberOfPlanes; i++)
    {
        planes.push_back(Plane(i));
    }

    std::vector<std::thread> planeThreads;
    for (int i = 0; i < numberOfPlanes; i++)
    {
        planeThreads.emplace_back(
            [i, &planes]()
            {
                planes[i].start(runway);
            });
    }

    for (auto& thread : planeThreads)
    {
        thread.join();
    }
}

int main()
{
    int nextId = 0;
    for (auto& gate : gates)
    {
        gate.setId(nextId++);
        gate.setRunway(runway);
    }
   
    while (true)
    {
        std::string input;
        std::cin >> input;

        if (input[0] == 'p') 
        {
            int numberOfPassengers = std::stoi(input.substr(1, input.length() - 1));
            std::thread(addPassengers, numberOfPassengers).detach();
        }

        if (input[0] == 'a') 
        {
            int numberOfPlanes = std::stoi(input.substr(1, input.length() - 1));
            std::thread(addPlanes, numberOfPlanes).detach();
        }
    }

    return 0;
}