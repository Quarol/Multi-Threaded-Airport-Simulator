#include "Plane.hpp"

#include "Runway.hpp"
#include "Constants.hpp"
#include "Utils.hpp"

Plane::Plane()
    : id_(1)
    , passengerCount_(0)
    , readyToStart_(false)
{}

Plane::Plane(int id)
    : id_(id)
    , passengerCount_(0)
    , readyToStart_(false)
{}

void Plane::start(std::shared_ptr<Runway> runway)
{
    runway_ = runway;

    while (true) 
    {
        runway_->movePassengersToPlane(Constants::PASSENGERS_PER_PLANE);

        std::cout << "Plane " << Utils::addBrackets(id_)
            << " is starting with: " << Constants::PASSENGERS_PER_PLANE << " passengers." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(Constants::PLANE_START_TIME));

        land();
    }
}

void Plane::land()
{
    std::cout << "Plane " << Utils::addBrackets(id_)  
        << " has landed" << std::endl;
}

