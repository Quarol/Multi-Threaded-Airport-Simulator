#pragma once
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class Plane {
public:
    Plane(int id, int gateId);
    Plane(const Plane&) = delete; // Delete copy constructor
    Plane& operator=(const Plane&) = delete; // Delete copy assignment operator
    void addPassenger();
    void start(std::shared_ptr<Counter> counter);
    void land();
private:
    int id_;
    int gateId_;
    int passengerCount_;
    std::mutex planeMutex_;
    std::condition_variable planeCV_;
    bool readyToStart_;
};
