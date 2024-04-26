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

	void best_params_ga()
	{
		/*
			Objective:
		*/

		GA_Params best;
		utilities::param.ga_p.max_generations = 10000;
		LD best_res =INF;

		for (int elite= 1; elite <= 50; elite++)
		for (int max_population=50; max_population<=200; max_population+=10)
		for (int roulette = 30; roulette<=100; roulette+=10)
		for (int opt_path_swap_it = 10; opt_path_swap_it<=50; opt_path_swap_it+=10)
		for (int alpha = 1; alpha<=100; alpha++)
		for (int tx_mutation_AHCAVG = 1; tx_mutation_AHCAVG < 100; tx_mutation_AHCAVG++)
		for (int fix_init = -1; fix_init < utilities::n_cities; fix_init++)
		for (int bcr = 0; bcr<2; bcr++)
		for (int AHCAVG = 0; AHCAVG<2; AHCAVG++)
		for (int CX = 0; CX<2 &&  bcr+CX+AHCAVG > 0; CX++)
		for(int j=0; j<3; j++)
		{
			utilities::param.ga_p.max_population = max_population;
			utilities::param.ga_p.tx_elite = (utilities::param.ga_p.max_population*elite)/100 ;
			utilities::param.ga_p.roulette = roulette;
			utilities::param.ga_p.opt_path_swap_it = opt_path_swap_it;
			utilities::param.ga_p.alpha = alpha;
			utilities::param.ga_p.tx_mutation_AHCAVG = tx_mutation_AHCAVG;
			utilities::param.ga_p.fix_init = fix_init;
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
			LD res = a.activate();

			if(res<best_res)
			{
				best = utilities::param.ga_p;
			}
			cout << "Ultimo: " << res << " Melhor: " << best_res <<endl;
		}

		ofstream out_best(BEST_PARAMS_FILE);
		out_best << "genetic" <<endl;
		out_best << "genetic.tx_elite "<< best.tx_elite <<endl;
		out_best << "genetic.max_population "<< best.max_population <<endl;
		out_best << "genetic.roulette "<< best.roulette <<endl;
		out_best << "genetic.tx_elite "<< best.opt_path_swap_it <<endl;
		out_best << "genetic.alpha "<< best.alpha <<endl;
		out_best << "genetic.tx_mutation_AHCAVG "<< best.tx_mutation_AHCAVG <<endl;
		out_best << "genetic.fix_init "<< best.fix_init <<endl;
		for(string e : best.cross_active)
		{
			out_best << "genetic.cross_active." << e<< " " << best.fix_init <<endl;
		}
		out_best << "end" <<endl;
	}
};
