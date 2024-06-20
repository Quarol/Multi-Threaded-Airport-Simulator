#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "Runway.hpp"

class Plane {
public:
    Plane();
    Plane(int id);

    void start(std::shared_ptr<Runway> runway);

private:
    int id_;
    int passengerCount_;

    std::shared_ptr<Runway> runway_;
};
