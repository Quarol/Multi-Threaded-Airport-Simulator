#include "Plane.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Counter.hpp"

Plane::Plane(int id, int gateId)
    : id_(id), gateId_(gateId), passengerCount_(0), readyToStart_(false)
{}

void Plane::addPassenger()
{
    std::unique_lock<std::mutex> lock(planeMutex_);
    passengerCount_++;
    if (passengerCount_ == Constants::PASSENGERS_PER_PLANE)
    {
        readyToStart_ = true;
        planeCV_.notify_one();
    }
}

void Plane::start(std::shared_ptr<Counter> counter)
{
    while (true) 
    {
        std::unique_lock<std::mutex> lock(planeMutex_);
        planeCV_.wait(lock, [this, counter]() { return counter->movePeopleToPlane(Constants::PASSENGERS_PER_PLANE); });
        readyToStart_ = false;

        std::cout << "Plane " << Utils::addBrackets(id_)
            << " at gate " << Utils::addBrackets(gateId_)
            << " is starting with " << Constants::PASSENGERS_PER_PLANE << " passengers." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(Constants::PLANE_START_TIME));

        land();
    }
}

void Plane::land()
{
    {
        std::cout << "Plane " << Utils::addBrackets(id_)
                  << " at gate " << Utils::addBrackets(gateId_)
                  << " has landed." << std::endl;
    
        std::lock_guard<std::mutex> lock(planeMutex_);
        passengerCount_ = 0;
        readyToStart_ = false;
    }
}
