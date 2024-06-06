
#include "Passenger.hpp"

#include <iostream>

#include "Utils.hpp"

Passenger::Passenger(const std::string& name, const int age)
	: name_(name)
	, age_(age)
{
	std::cout << "Passenger " << Utils::addBrackets(name_)  
		<< ", Age " << age_ << std::endl;
}

std::string Passenger::getName() const
{
	return name_;
}

int Passenger::getAge() const
{
	return age_;
}