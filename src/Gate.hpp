#pragma once

#include <mutex>
#include <condition_variable>

#include "Passenger.hpp"

class Gate 
{
public:
	Gate();

	void occupyGate();
	void releaseGate();
	void assignPassenger(Passenger& passenger);


private:
	const int CHECKIN_TIME = 2;
	
	std::mutex gateMutex_;
	std::condition_variable gateAvailable_;
	bool isAvailable_ = true;
};
