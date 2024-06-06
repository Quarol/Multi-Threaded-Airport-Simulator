#pragma once

#include <mutex>
#include <condition_variable>
#include <vector>

#include "Passenger.hpp"
#include "Plane.hpp"
#include "Runway.hpp"

class Gate 
{
public:
    Gate();
    void assignPassenger(Passenger& passenger);
    int getPassengerCount();

public:
    void setId(int id);
    void setRunway(std::shared_ptr<Runway> runway);

    std::mutex& getMutex();
    std::shared_ptr<Runway> getRunway();
   
private:
    void occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime);
    void releaseGate();

private:
    int id_;
    int passengerCount_;
    bool isAvailable_;

    std::shared_ptr<Runway> runway_;
    std::mutex gateMutex_;
    std::condition_variable gateAvailableCV_;
};
