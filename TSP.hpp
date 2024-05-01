#pragma once
#include "library.hpp"
#include "genetic.hpp"
#include "annealing.hpp"

class TSP
{

public:
	void run()
	{
		genetic ga(utilities::n_cities);
		LD best= INF;
		vector<int> path;
		if(utilities::param.hybrid[0])
		{	
			ga.activate();
			best = ga.best_fit();
			path = ga.best_path();
		}

		if(utilities::param.hybrid[1])
		{
			annealing ann(path, best);
			best = min(best,ann.solution());
		}
		
		cout << best <<endl;
	}
};
