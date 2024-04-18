
#include "Gate.hpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

Gate::Gate()
    : isAvailable_(true)
{
}

void Gate::occupyGate() {
    std::unique_lock<std::mutex> lock(gateMutex_);
    while (!isAvailable_) {
        gateAvailable_.wait(lock);
    }
    isAvailable_ = false;
}

void Gate::releaseGate() {
    {
        std::lock_guard<std::mutex> lock(gateMutex_);
        isAvailable_ = true;
    }
    gateAvailable_.notify_one();
}

void Gate::assignPassenger(Passenger& passenger) {
    occupyGate();
    // Przypisanie pasa¿era do bramki
    // ...
    // Symulacja procesu odprawy
    std::cout << "Passenger assigned to gate." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(CHECKIN_TIME)); // Symulacja czasu odprawy
    releaseGate();
}