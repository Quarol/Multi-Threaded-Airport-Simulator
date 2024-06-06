
#include "Runway.hpp"
#include <iostream>

Runway::Runway(int id)
	: id_(id)
	, passengersPastGates_(0)
	, isAvailable_(true)
{}

void Runway::addPassengersPastGates(int numberOfPassengers)
{
	std::unique_lock<std::mutex> lock(runwayMutex_);
	passengersPastGates_ += numberOfPassengers;
	runwayAvailableCV_.notify_all();
}

void Runway::movePassengersToPlane(int numberOfPassengers)
{
	std::unique_lock<std::mutex> lock(runwayMutex_);
	runwayAvailableCV_.wait(lock, [this, numberOfPassengers]() { return passengersPastGates_ >= numberOfPassengers; });

	passengersPastGates_ -= numberOfPassengers;

	std::cout << "Moved " << numberOfPassengers << " passengers from runway to plane. Remaining: " << passengersPastGates_ << std::endl;
	runwayAvailableCV_.notify_all();
}

int Runway::getPassengersPastGates()
{
	return passengersPastGates_;
}