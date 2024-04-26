#pragma once

#include <mutex>
#include <condition_variable>

#include "Passenger.hpp"

class Gate 
{
public:
	Gate();
	void assignPassenger(Passenger& passenger);
	void setId(int id);

private:
	void occupyGate();
	void releaseGate();

private:
	std::mutex gateMutex_;
	std::condition_variable gateAvailableCV_;

	int id_;
	bool isAvailable_ = true;
};
