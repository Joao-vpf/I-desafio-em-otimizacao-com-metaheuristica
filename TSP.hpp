#pragma once
#include "library.hpp"
#include "genetic.hpp"
#include "annealing.hpp"
#include "grasp.hpp"

class TSP
{

public:
	void run()
	{
		auto start = chrono::system_clock::now();
		genetic ga(utilities::n_cities);
		LD best = INF;
		vector<int> path;
		if (utilities::param.hybrid[0])
		{
			ga.activate();
			best = ga.best_fit();
			path = ga.best_path();
		}

		if (utilities::param.hybrid[1])
		{
			annealing ann(path, best);
			LD best_ann = ann.solution();
			
			if (best_ann < best)
			{
				best = best_ann;
				path = ann.best_solution;
			}
		}

		if (utilities::param.hybrid[2])
		{
			grasp gra(path, best);
			LD best_gra = gra.solution();

			if (best_gra < best)
			{
				best = best_gra;
				path = gra.best_solution;
			}
		}

    	auto end = chrono::system_clock::now();
		chrono::duration<double> time = end - start;
		cout << "Tempo decorrido: " << time.count() << " segundos" << endl;
		cout << best << endl;
	}
};
