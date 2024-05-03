#pragma once
#include "library.hpp"
#include "genetic.hpp"
#include "annealing.hpp"
#include "ACO.hpp"
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

		for(int i = 0;i<utilities::n_cities;i++){
			path.push_back(i);
		}
		best=utilities::Fx_fit(path,utilities::n_cities);
		
		if (utilities::param.hybrid[0])
		{
			ga.activate();
			best = ga.best_fit();
			path = ga.best_path();
			ACO aco(path);
			aco.active();
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
		cout << "path: ";
		for(auto i :path)cout<<i<<" ";

	}

	void best_params()
	{
		LD best = INF, min_time = INF;
		LD best_med =0, current_time = INF;
		for(int j=0; j<5; j++)
		{
			auto start = chrono::system_clock::now();
			genetic ga(utilities::n_cities);
			ga.activate();
			best_med += ga.best_fit();
			auto end = chrono::system_clock::now();
			chrono::duration<double> time = end - start;
			if(time.count() < current_time) 
				current_time = time.count();
		}
		best = best_med/5;
		min_time = current_time;
		cout  << "Melhor media de resposta: " << best << " Menor tempo de execucao: " <<  min_time <<endl; 
	}
};
