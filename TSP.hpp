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
		for (int opt_path_swap_it = 10; opt_path_swap_it < 60; opt_path_swap_it+=10)
		for (int elite = 10; elite <= 50; elite+=10)
		for (int alpha = 10; alpha<60; alpha+=10)
		for (int P_limiar = 2; P_limiar < 10; P_limiar++)
		for (int P_value = 10; P_value < 50; P_value+=10)
		for (int roulette = 10; roulette < 110; roulette+=10)
		for (int tx_mutation_AHCAVG = 10; tx_mutation_AHCAVG < 80; tx_mutation_AHCAVG+=10)
		for (int bcr = 0; bcr<2; bcr++)
		for (int AHCAVG = 0; AHCAVG<2; AHCAVG++)
		for (int vr = 0; vr<2; vr++)
		for (int er = 0; er<2 && er+bcr+vr+AHCAVG>0; er++)
		{
			LD best_res =0;
			for(int j=0; j<2; j++)
			{
				utilities::param.ga_p = GA_Params();
				utilities::param.ga_p.max_generations = 10000;
				utilities::param.ga_p.verbose = 0;
				utilities::param.ga_p.max_population = 100;
				utilities::param.ga_p.tx_elite = (utilities::param.ga_p.max_population*elite)/100 ;
				utilities::param.ga_p.roulette = roulette;
				utilities::param.ga_p.P_limiar = P_limiar;
				utilities::param.ga_p.P_value = P_value;
				utilities::param.ga_p.opt_path_swap_it = opt_path_swap_it;
				utilities::param.ga_p.alpha = alpha;
				utilities::param.ga_p.tx_mutation_AHCAVG = tx_mutation_AHCAVG;
				utilities::param.ga_p.cross_active_delete("CX");
				if (bcr == 0)
					utilities::param.ga_p.cross_active_delete("BCR");
				else
					utilities::param.ga_p.cross_active_insert("BCR");
				if (AHCAVG == 0)
					utilities::param.ga_p.cross_active_delete("AHCAVG");
				else
					utilities::param.ga_p.cross_active_insert("AHCAVG");
				if (vr == 0)
					utilities::param.ga_p.cross_active_delete("VR");
				else
					utilities::param.ga_p.cross_active_insert("VR");
				if (er == 0)
					utilities::param.ga_p.cross_active_delete("er");
				else
					utilities::param.ga_p.cross_active_insert("er");
				
				utilities::param.ga_p.number_active_cross = utilities::param.ga_p.cross_active.size();
				genetic a(utilities::n_cities);
				best_res += a.activate();
			}

			if(best_res/2 < best_med)
			{
				best_med = best_res/2;
				best = utilities::param.ga_p;
				best.tx_elite = elite;
				
				cout << "genetic" <<endl;
				cout << "genetic.tx_elite "<< best.tx_elite <<endl;
				cout << "genetic.max_population "<< best.max_population <<endl;
				cout << "genetic.roulette "<< best.roulette <<endl;
				cout << "genetic.opt_path_swap_it "<< best.opt_path_swap_it <<endl;
				cout << "genetic.alpha "<< best.alpha <<endl;
				cout << "genetic.tx_mutation_AHCAVG "<< best.tx_mutation_AHCAVG <<endl;
				cout << "genetic.P_limiar "<< best.P_limiar <<endl;
				cout << "genetic.P_value "<< best.P_value <<endl;
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
