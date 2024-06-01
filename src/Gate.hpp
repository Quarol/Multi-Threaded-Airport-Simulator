#ifndef GATE_HPP
#define GATE_HPP

#include <mutex>
#include <condition_variable>
#include <vector>
#include "Passenger.hpp"

class Gate {
public:
    Gate();
    void setId(int id);
    void assignPassenger(Passenger& passenger);
    std::mutex& getMutex();
    int getPassengerCount();

private:
    int id_;
    bool isAvailable_;
    int passengerCount_;
    std::mutex gateMutex_;
    std::condition_variable gateAvailableCV_;
    void occupyGate(std::chrono::time_point<std::chrono::steady_clock>& startTime);
    void releaseGate();
};

#endif // GATE_HPP
