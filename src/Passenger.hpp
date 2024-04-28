#pragma once
#include <string>


class Passenger
{
public:
	Passenger(const std::string& name, const int age);


	std::string getName() const;
	int getAge() const;
	bool canYield() const;
	void yield() const;

private:
	std::string name_;
	int age_;
	int yieldCounter_ = 0;
};