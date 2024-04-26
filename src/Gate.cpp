
#include "Gate.hpp"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

#include "Constants.hpp"

Gate::Gate()
    : id_(1)
    , isAvailable_(true)
{
}

void Gate::occupyGate() 
{
    std::unique_lock<std::mutex> lock(gateMutex_);
    gateAvailableCV_.wait(lock, [this]() { return isAvailable_; });
    isAvailable_ = false;
}

void Gate::releaseGate() 
{
    {
        std::lock_guard<std::mutex> lock(gateMutex_);
        isAvailable_ = true;
    }
    gateAvailableCV_.notify_one();
}

void Gate::assignPassenger(Passenger& passenger) 
{
    occupyGate();
    std::cout << "Passenger: " << passenger.getName() << ", assigned to gate: " << id_ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(Constants::CHECKIN_TIME));
    releaseGate();
}

void Gate::setId(int id)
{
    id_ = id;
}