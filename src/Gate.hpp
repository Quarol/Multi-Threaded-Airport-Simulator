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
    void addPlane();
    int getPassengerCount();

public:
    void setId(int id);
    void setRunway(std::shared_ptr<Runway> runway);
    std::mutex& getMutex();
    //std::vector<std::unique_ptr<Plane>> planes_;
    std::shared_ptr<Runway> runway_;

private:
    void occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime);
    void releaseGate();

    int id_;
    int passengerCount_;

    bool isAvailable_;
  
    std::mutex gateMutex_;
    std::condition_variable gateAvailableCV_;
};
