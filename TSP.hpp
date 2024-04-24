#pragma once
#include "library.hpp"
#include "genetic.hpp"

class TSP
{
public:
	void run()
	{
		genetic a(utilities::n_cities);
		a.activate();
	}
};
