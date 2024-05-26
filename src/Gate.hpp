#pragma once

#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

#include "Passenger.hpp"

class Gate
{
	using priorityAndThread = std::pair<int, std::function<void()>>;

public:
	Gate();
	void assignPassenger(Passenger& passenger);
	void setId(int id);

private:
	void occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime);
	void releaseGate();

private:
	std::mutex gateMutex_;
	std::condition_variable gateAvailableCV_;

	int id_;
	bool isAvailable_ = true;
};
