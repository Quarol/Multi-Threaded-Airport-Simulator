#include "Gate.hpp"
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <chrono>

#include "Constants.hpp"
#include "Utils.hpp"

Gate::Gate()
    : id_(1), isAvailable_(true), passengerCount_(0)
{
    for (int i = 0; i < 1; i++) 
    {
        planes_.emplace_back(std::make_unique<Plane>(i, id_));
    }
}

void Gate::occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime) 
{
    std::this_thread::sleep_for(std::chrono::seconds(Utils::generateRandomNumber()));
    std::unique_lock<std::mutex> lock(gateMutex_);

    startTime = std::chrono::steady_clock::now();

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
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    occupyGate(startTime);
    auto endTime = std::chrono::steady_clock::now();
    auto waitingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    std::cout << "Passenger: " << Utils::addBrackets(passenger.getName()) << ", assigned to gate: " << Utils::addBrackets(id_)
        << ", waited for: " << waitingTime << " ms" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(Constants::CHECKIN_TIME));

    counter_->addPeoplePastGates();

    releaseGate();
    passengerCount_++;
}

void Gate::addPlane() 
{
    int newPlaneId = planes_.size();
    planes_.emplace_back(std::make_unique<Plane>(newPlaneId, id_));
}

void Gate::setId(int id) {
    id_ = id;
}

std::mutex& Gate::getMutex() {
    return gateMutex_;
}

int Gate::getPassengerCount() {
    return passengerCount_;
}