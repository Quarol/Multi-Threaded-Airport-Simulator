#pragma once

#include <string>

class Passenger
{
public:
	Passenger(const std::string& name, const int age);

public:
	std::string getName() const;
	int getAge() const;

private:
	std::string name_;
	int age_;
};