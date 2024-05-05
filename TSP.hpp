#pragma once
#include "library.hpp"
#include "genetic.hpp"
#include "annealing.hpp"
#include "ACO.hpp"
#include "grasp.hpp"
#include "ABC.hpp"


class TSP
{
	/*
		Objective:
			Class for solving the Traveling Salesman Problem (TSP) using various optimization algorithms.
	*/

	void active_metrics(LD best)
	{
		/*
			Objective:
				Activates and calculates metrics based on the best solution found.

			Parameters:
				- best: The best fitness value obtained.
		*/

		if(utilities::param.metrics[0])
			cout << "**MAE:** "<< utilities::calculateMAE(best, utilities::input_predicted) << endl;

		if(utilities::param.metrics[1])
			cout << "**MSE:** "<< utilities::calculateMSE(best, utilities::input_predicted) <<endl;

		if(utilities::param.metrics[2])
			cout << "**R2:** "<< utilities::calculateR2(best, utilities::input_predicted) << endl;
	}

public:
	void run()
	{
		/*
			Objective:
				Run the TSP solver using different hybrid optimization algorithms.

		*/
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

		if (utilities::param.hybrid[3])
		{
			ACO aco(path);
			aco.active();
			LD best_aco_fit = aco.get_best_fit();
			
			if(best_aco_fit < best)
			{
				best = best_aco_fit;
				path = aco.get_best_path();
			}
		}

		if (utilities::param.hybrid[4])
		{
			ABC abc(path, best);
			LD best_abc = abc.solution();

			if (best_abc < best)
			{
				best = best_abc;
				path = abc.best_solution;
			}
		}
		
    	auto end = chrono::system_clock::now();
		chrono::duration<double> time = end - start;
		cout << "**Elapsed Time:** " << time.count() << " seconds" << endl;
		cout << "**Fit:** "<< best << endl;
		cout << "**path:** ";
		for(auto i :path)cout<<i<<" ";
		cout <<endl;

		if(utilities::param.metrics[0] + utilities::param.metrics[1] + utilities::param.metrics[2])
		{
			active_metrics(best);
		}
	}

	void best_params()
	{
		/*
			Objective:
				Finds the best average fitness and the shortest execution time among multiple runs of a genetic algorithm.

		*/
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
		cout  << "Best average fitness: " << best << " Shortest execution time: " <<  min_time <<endl; 
	}
};
