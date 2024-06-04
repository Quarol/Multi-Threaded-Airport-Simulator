#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Runway.hpp"

class Plane {
public:
    Plane();
    Plane(int id, int gateId);
    void start(std::shared_ptr<Runway> runway);
    void land();

public:
    //void setRunway(std::shared_ptr<Runway> runway);

private:
    int id_;
    int gateId_;
    int passengerCount_;
    bool readyToStart_;
    std::shared_ptr<Runway> runway_;
};
