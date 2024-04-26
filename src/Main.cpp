#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>

#include "Constants.hpp"
#include "Gate.hpp"
#include "PassengerFactory.hpp"



int main() {

    std::vector<Gate> gates(Constants::NUMBER_OF_GATES);
    int nextId = 0;
    for (auto& gate : gates) { gate.setId(nextId++); }

    PassengerFactory* passengerFactory = new PassengerFactory;
    std::vector<Passenger> passengers = passengerFactory->createMultiplePassengers(200);

    // Przydzia³ pasa¿erów do bramek
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

    // Czekanie na zakoñczenie w¹tków pasa¿erów
    for (auto& passengerThread : passengerThreads) 
    {
        passengerThread.join();
    }

    return 0;
}