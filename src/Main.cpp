#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <memory>
#include <ncurses.h>
#include <chrono>

#include "Plane.hpp"
#include "Gate.hpp"
#include "Runway.hpp"
#include "PassengerFactory.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Output.hpp"

std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
auto runway = std::make_shared<Runway>(1);
auto passengerFactory = std::make_shared<PassengerFactory>();

int selectGateNumber(int i) 
{
    return i % gates.size();
}

void addPassengers(int numberOfPassengers) 
{   
    /*
    OutputHandler::writeMessage(
        "Starting to add " + Utils::addBrackets(numberOfPassengers) + " passengers\n"
    );
    */

    std::vector<Passenger> passengers = passengerFactory->createMultiplePassengersWithLogger(numberOfPassengers);

    std::vector<std::thread> passengerThreads;
    for (int i = 0; i < passengers.size(); i++) 
    {
        int gateid = selectGateNumber(i);

        passengerThreads.emplace_back(
            [gateid, passenger = std::move(passengers[i])] () mutable 
            {
                gates[gateid].assignPassenger(passenger);
            }
        );
    }

    for (auto& thread : passengerThreads) 
    {
        thread.join();
    }

    /*
    OutputHandler::writeMessage(
        "Finished adding " + Utils::addBrackets(numberOfPassengers) + " passengers"
    );
    */
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
            }
        );
    }

    for (auto& thread : planeThreads) 
    {
        thread.join();
    }
}

void setAttack(bool underAttack) 
{
    runway->setIsUnderAttack(underAttack);
    for (auto& gate : gates) 
    {
        gate.setIsUnderAttack(underAttack);
    }

    OutputHandler::setIsTerroristAttackOn(underAttack);
}

int main() 
{
    OutputHandler::initGUI();

    int numberOfPassengers;
    int numberOfPlanes;
    bool underAttack = false;

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

        switch (input[0]) 
        {
            case 'p':
                if (input.length() == 1)
                    break;

                numberOfPassengers = std::stoi(input.substr(1, input.length() - 1));
                std::thread(addPassengers, numberOfPassengers).detach();
                break;

            case 'a':
                if (input.length() == 1)
                    break;

                numberOfPlanes = std::stoi(input.substr(1, input.length() - 1));

                std::thread([numberOfPlanes]() {
                    OutputHandler::addPlanes(numberOfPlanes);
                }).detach();
                std::thread(addPlanes, numberOfPlanes).detach();

                break;

            case 'x':
                underAttack = !underAttack;
                std::thread(setAttack, underAttack).detach();
                break;
        }
    }

    return 0;
}
