#pragma once

#include <mutex>
#include <condition_variable>
#include <vector>
#include "Passenger.hpp"
#include "Plane.hpp"
#include "Counter.hpp"

class Gate {
public:
    Gate();
    void setId(int id);
    void assignPassenger(Passenger& passenger);
    std::mutex& getMutex();
    void addPlane();
    int getPassengerCount();

private:
    int id_;
    bool isAvailable_;
    int passengerCount_;
    std::mutex gateMutex_;
    std::condition_variable gateAvailableCV_;
    void occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime);
    void releaseGate();
    std::vector<std::unique_ptr<Plane>> planes_;
    std::shared_ptr<Counter> counter_;
};
