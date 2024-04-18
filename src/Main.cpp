#include <iostream>
#include <thread>
#include <mutex>
#include <vector>


#include "Gate.hpp"

int main() {
    Gate gate1, gate2;
    std::vector<Passenger> passengers = {
        Passenger("John", 25),
        Passenger("Alice", 30),
        Passenger("Bob", 40) 
    };

    // Przydzia³ pasa¿erów do bramek
    std::vector<std::thread> passengerThreads;
    for (Passenger& passenger : passengers) {
        passengerThreads.emplace_back([&]() {
            // Symulacja przydzia³u pasa¿erów do bramek
            if (rand() % 2 == 0) {
                gate1.assignPassenger(passenger);
            }
            else {
                gate2.assignPassenger(passenger);
            }
            });
    }

    // Czekanie na zakoñczenie w¹tków pasa¿erów
    for (auto& passengerThread : passengerThreads) {
        passengerThread.join();
    }

    return 0;
}