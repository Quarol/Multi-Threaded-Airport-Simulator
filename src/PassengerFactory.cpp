#include "PassengerFactory.hpp"
#include <sstream>

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

std::vector<Passenger> PassengerFactory::createMultiplePassengersWithLogger(int numberOfPassengers)
{
	std::vector<Passenger> passengers;
	passengers.reserve(numberOfPassengers);

	for (int i = 0; i < numberOfPassengers; i++)
	{
		std::stringstream ss;
		ss << "Passenger [" << numberOfPassengers << "]";
		std::string passengerName = ss.str();
		passengers.push_back(Passenger(passengerName, i));
	}

	return passengers;
}