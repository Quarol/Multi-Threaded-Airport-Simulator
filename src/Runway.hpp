#pragma once

#include <mutex>
#include <condition_variable>

class Runway 
{
public:
	Runway(int id);

	void addPassengersPastGates(int numberOfPassenger);
	void movePassengersToPlane(int numberOfPassenger);
	int getPassengersPastGates();

public:
	void setIsUnderAttack(bool underAttack);

private:
	int id_;
	int passengersPastGates_;
	bool isAvailable_;
	bool isUnderAttack_;

	std::mutex runwayMutex_;
	std::condition_variable runwayAvailableCV_;

};