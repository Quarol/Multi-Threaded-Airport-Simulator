
#include "Passenger.hpp"

#include <iostream>

Passenger::Passenger(const std::string& name, const int age)
	: name_(name)
	, age_(age)
{
	std::cout << "Passenger: " << name_ << ", Age: " << age_ << std::endl;
}

std::string Passenger::getName() const
{
	return name_;
}

int Passenger::getAge() const
{
	return age_;
}

bool Passenger::canYield() const
{
	return yieldCounter_ < YIELD_LIMIT;
}

void Passenger::yield() const
{
	yieldCounter_++;
}