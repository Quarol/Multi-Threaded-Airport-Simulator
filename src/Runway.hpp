#pragma once

#include <mutex>
#include <condition_variable>

class Runway 
{
public:
	Runway();
	void addPassengersPastGates(int numberOfPassenger);
	void movePassengersToPlane(int numberOfPassenger);
	int getPassengersPastGates();

private:
	void unlockMutex();
	void lockMutex(int numberOfPassengers);

private:
	int passengersPastGates_;
	bool isAvailable_;

	std::mutex runwayMutex_;
	std::condition_variable runwayAvailableCV_;
};