
#include "Runway.hpp"
#include <iostream>

Runway::Runway()
	: passengersPastGates_(0)
	, isAvailable_(true)
{
	std::cout << "Runway initialized";
}

void Runway::addPassengersPastGates(int numberOfPassengers)
{
	std::unique_lock<std::mutex> lock(runwayMutex_);
	passengersPastGates_ += numberOfPassengers;

	runwayAvailableCV_.notify_all();
}

void Runway::movePassengersToPlane(int numberOfPassengers)
{
	//lockMutex(numberOfPassengers);
	// Wait until there are enough passengers to move
	//runwayAvailableCV_.wait(lock, [this, numberOfPassengers]() { return passengersPastGates_ >= numberOfPassengers; });

	while (passengersPastGates_ < numberOfPassengers)
	{
		;
	}
	passengersPastGates_ -= numberOfPassengers;
	std::cout << "Moved " << numberOfPassengers << " passengers from runway to plane. Remaining: " << passengersPastGates_ << std::endl;
	//unlockMutex();
}

int Runway::getPassengersPastGates()
{
	return passengersPastGates_;
}

void Runway::unlockMutex()
{
	{
		std::lock_guard<std::mutex> lock(runwayMutex_);
		isAvailable_ = true;
	}
	runwayAvailableCV_.notify_one();
}

void Runway::lockMutex(int numberOfPassengers)
{
	std::unique_lock<std::mutex> lock(runwayMutex_);

	runwayAvailableCV_.wait(lock, [this, numberOfPassengers]() { return passengersPastGates_ >= numberOfPassengers && isAvailable_; });
	isAvailable_ = false;
}