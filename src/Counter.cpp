#include "Counter.hpp"

void Counter::addPeoplePastGates(int numberOfPeople = 1)
{
	peoplePastGates_ += numberOfPeople;
}

void Counter::movePeopleToPlane(int numberOfPeople)
{
	peoplePastGates_ -= numberOfPeople;
}

int Counter::getPeoplePastGates()
{
	return peoplePastGates_;
}