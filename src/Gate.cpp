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
    : id_(1)
    , isAvailable_(true)
    , passengerCount_(0)
{}

void Gate::occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime, bool& timedOut) 
{
    //std::this_thread::sleep_for(std::chrono::seconds(Utils::generateRandomNumber()));
    std::unique_lock<std::mutex> lock(gateMutex_);

    startTime = std::chrono::steady_clock::now();
    auto timeout = std::chrono::seconds(Constants::MAX_WAIT_TIME);

    if (!gateAvailableCV_.wait_for(lock, timeout, [this]() { return isAvailable_; })) {
        // Timeout occurred
        timedOut = true;
        return;
    }

    isAvailable_ = false;
    timedOut = false;
}

void Gate::releaseGate()
{
    isAvailable_ = true;
    gateAvailableCV_.notify_all();
}

void Gate::assignPassenger(Passenger& passenger) 
{
    bool timedOut;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    occupyGate(startTime, timedOut);
    auto endTime = std::chrono::steady_clock::now();
    auto waitingTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    if (timedOut)
    {
        std::cout << "Passenger " << Utils::addBrackets(passenger.getName())
            << ", waited TOO LONG." << "Redirected to golden gate."
            << "Waiting time: " << waitingTime << " ms" << std::endl;

        runway_->addPassengersPastGates(1);
        releaseGate();
        passengerCount_++;

        return;
    }

    std::cout << "Passenger " << Utils::addBrackets(passenger.getName())
        << ", assigned to gate " << Utils::addBrackets(id_)
        << ", waited for: " << waitingTime << " ms" << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(Constants::CHECKIN_TIME));

    runway_->addPassengersPastGates(1);

    releaseGate();
    passengerCount_++;
}

void Gate::setId(int id) 
{
    id_ = id;
}

void Gate::setRunway(std::shared_ptr<Runway> runway)
{
    runway_ = runway;
}

std::mutex& Gate::getMutex() 
{
    return gateMutex_;
}

int Gate::getPassengerCount() 
{
    return passengerCount_;
}

std::shared_ptr<Runway> Gate::getRunway()
{
    return runway_;
}