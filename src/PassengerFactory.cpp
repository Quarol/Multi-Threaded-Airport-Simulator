#pragma once

#include "PassengerFactory.hpp"

std::vector<Passenger> PassengerFactory::createMultiplePassengers(int numberOfPassengers)
{
	std::vector<Passenger> passengers;
	passengers.reserve(numberOfPassengers);

	for (int i = 0; i < numberOfPassengers; i++)
	{
		passengers.push_back(Passenger(randomNames_[i % numberOfPassengers], i));
	}

	return passengers;
}