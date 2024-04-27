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

	void best_params_ga()
	{
		/*
			Objective:
		*/

		GA_Params best;
		LD best_med = INF;
		for (int elite = 10; elite <= 50; elite+=10)
		for (int alpha = 10; alpha<60; alpha+=10)
		for (int tx_mutation_AHCAVG = 10; tx_mutation_AHCAVG < 40; tx_mutation_AHCAVG+=10)
		for (int bcr = 0; bcr<2; bcr++)
		for (int AHCAVG = 0; AHCAVG<2 && bcr+AHCAVG > 0; AHCAVG++)
		for (int CX = 0; CX<2; CX++)
		{
			LD best_res =0;
			for(int j=0; j<3; j++)
			{
				utilities::param.ga_p = GA_Params();
				utilities::param.ga_p.max_generations = 5000;
				utilities::param.ga_p.verbose = 0;
				utilities::param.ga_p.max_population = 50;
				utilities::param.ga_p.tx_elite = (utilities::param.ga_p.max_population*elite)/100 ;
				utilities::param.ga_p.roulette = 10;
				utilities::param.ga_p.opt_path_swap_it = 10;
				utilities::param.ga_p.alpha = alpha;
				utilities::param.ga_p.tx_mutation_AHCAVG = tx_mutation_AHCAVG;
				if (bcr == 0)
					utilities::param.ga_p.cross_active_delete("BCR");
				else
					utilities::param.ga_p.cross_active_insert("BCR");
				if (AHCAVG == 0)
					utilities::param.ga_p.cross_active_delete("AHCAVG");
				else
					utilities::param.ga_p.cross_active_insert("AHCAVG");
				if (CX == 0)
					utilities::param.ga_p.cross_active_delete("CX");
				else
					utilities::param.ga_p.cross_active_insert("CX");
				
				utilities::param.ga_p.number_active_cross = utilities::param.ga_p.cross_active.size();
				genetic a(utilities::n_cities);
				best_res += a.activate();
			}

			if(best_res/3 < best_med)
			{
				best_med = best_res/3;
				best = utilities::param.ga_p;
				best.tx_elite = elite;
				
				cout << "genetic" <<endl;
				cout << "genetic.tx_elite "<< best.tx_elite <<endl;
				cout << "genetic.max_population "<< best.max_population <<endl;
				cout << "genetic.roulette "<< best.roulette <<endl;
				cout << "genetic.opt_path_swap_it "<< best.opt_path_swap_it <<endl;
				cout << "genetic.alpha "<< best.alpha <<endl;
				cout << "genetic.tx_mutation_AHCAVG "<< best.tx_mutation_AHCAVG <<endl;
				cout << "genetic.fix_init "<< best.fix_init <<endl;
				for(string e : best.cross_active)
				{
					cout << "genetic.cross_active." << e<< " " << 1 <<endl;
				}
				cout << "end" <<endl;
				cout<< endl;
			}
			cout << "Media atual: " << best_res << " Melhor media: " << best_med <<endl;
			cout << "###########################################" <<endl <<endl;;
		}

		ofstream out_best(BEST_PARAMS_FILE);
		out_best << "genetic" <<endl;
		out_best << "genetic.tx_elite "<< best.tx_elite <<endl;
		out_best << "genetic.max_population "<< best.max_population <<endl;
		out_best << "genetic.roulette "<< best.roulette <<endl;
		out_best << "genetic.opt_path_swap_it "<< best.opt_path_swap_it <<endl;
		out_best << "genetic.alpha "<< best.alpha <<endl;
		out_best << "genetic.tx_mutation_AHCAVG "<< best.tx_mutation_AHCAVG <<endl;
		out_best << "genetic.fix_init "<< best.fix_init <<endl;
		for(string e : best.cross_active)
		{
			out_best << "genetic.cross_active." << e<< " " << 1 <<endl;
		}
		out_best << "end" <<endl;
	}
};
