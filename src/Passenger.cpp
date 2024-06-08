
#include "Passenger.hpp"

#include <iostream>

#include "Utils.hpp"

Passenger::Passenger(const std::string& name, const int age)
	: name_(name)
	, age_(age)
{
}

std::string Passenger::getName() const
{
	return name_;
}

int Passenger::getAge() const
{
	return age_;
}