#include "Plane.hpp"

#include "Runway.hpp"
#include "Constants.hpp"
#include "Utils.hpp"
#include "Output.hpp"

Plane::Plane()
    : id_(1)
    , passengerCount_(0)
{}

Plane::Plane(int id)
    : id_(id)
    , passengerCount_(0)
{}

void Plane::start(std::shared_ptr<Runway> runway)
{
    std::string message;
    runway_ = runway;

    runway_->movePassengersToPlane(Constants::PASSENGERS_PER_PLANE);

    std::this_thread::sleep_for(std::chrono::seconds(Constants::PLANE_START_TIME));
    OutputHandler::adjustAfterFlight();

    /*
    message = "Plane " + Utils::addBrackets(id_) +
        " is starting with: " + std::to_string(Constants::PASSENGERS_PER_PLANE) + " passengers.\n";
    OutputHandler::writeMessage(message);
    */
    //OutputHandler::writeMessage("Plane " + Utils::addBrackets(id_) + " has landed\n");
}
