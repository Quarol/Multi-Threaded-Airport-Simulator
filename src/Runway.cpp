
#include "Runway.hpp"

#include <iostream>
#include <thread>
#include <ncurses.h>

#include "Output.hpp"
#include "Utils.hpp"

Runway::Runway(int id)
	: id_(id)
	, passengersPastGates_(0)
	, isAvailable_(true)
	, isUnderAttack_(false)
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
	runwayAvailableCV_.wait(lock, 
		[this, numberOfPassengers]() 
		{ 
			return ((passengersPastGates_ >= numberOfPassengers) && !isUnderAttack_); 
		});

	passengersPastGates_ -= numberOfPassengers;

	/*
	OutputHandler::writeMessage(
		"Moved: " + std::to_string(numberOfPassengers) + " passengers from runway to plane" +
		", Remaining: " + std::to_string(passengersPastGates_) + "\n"
	);
	*/
	
	runwayAvailableCV_.notify_all();
}

int Runway::getPassengersPastGates()
{
	return passengersPastGates_;
}

void Runway::setIsUnderAttack(bool underAttack)
{
	isUnderAttack_ = underAttack;
	/*
	if (isUnderAttack_)
		OutputHandler::writeMessage("Runway has been stopped due to ongoing ATTACK!\n");
	else
		OutputHandler::writeMessage("Runway has been resumed due to the end of the ATTACK!\n");
	*/
}