#include "Plane.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Runway.hpp"

Plane::Plane()
    : id_(1)
    , passengerCount_(0)
    , readyToStart_(false)
{
}

Plane::Plane(int id, int gateId)
    : id_(id), gateId_(gateId), passengerCount_(0), readyToStart_(false)
{
    //std::cout << "Constructed Plane";
}

void Plane::start(std::shared_ptr<Runway> runway)
{
    runway_ = runway;

    //while (true) 
    //{
        std::cout << "before movePassengersToPlane";
        runway_->movePassengersToPlane(Constants::PASSENGERS_PER_PLANE);
        std::cout << "After movePassengersToPlane";

        std::cout << "Plane " << Utils::addBrackets(id_)
        << " is starting with " << Constants::PASSENGERS_PER_PLANE << " passengers." << std::endl;

        std::this_thread::sleep_for(std::chrono::seconds(Constants::PLANE_START_TIME));

        land();
    //}
}

void Plane::land()
{
    //std::cout << "Plane has landed";
}
//
//void Plane::setRunway()
//{
//    runway_ = runway;
//}
