#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

#define LL long long
#define ULL unsigned long long
#define LD long double
#define INF 1e16

using namespace std;

struct point {
	LD X, Y;
	point(LD x, LD y) : X(x), Y(y){}
};

class utilities
{
	/*
		Objetivo:
			Classe tem o objetivo de ter funções que seram utilizadas para outras heuristicas.
	*/

public:
	static LD euclidian_distance(point a, point b)
	{
		return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
	}

	static LD Fx_cust(vector<point>& city, vector<int>& vet, int n, bool ok)
	{
		LD cust = 0;
		for (int i = 0; i < n - 1; i++)
		{
			cust += utilities::euclidian_distance(city[vet[i]], city[vet[i + 1]]);
		}

		if (ok)
		{
			cust = INF - cust;
			return cust;
		}
		return cust;
	}

	static int random_range(int start, int end)
	{
		/*
			Objective:
				Find a random number between the start and end (excluding the end).
		*/

		if (start > end)
		{
			swap(start, end);
		}

		int range = end - start;

		if(range >0)
			return start + rand() % range;
		
		return start - 1;
	}
};

struct GA_Params
{
	/*
		Objective:
			Class aimed at defining the parameters that will be used in the genetic algorithm.

		Attributes:
			max_generations = Maximum number of generations.
			max_population = Maximum number of genes in the population.
			roulette = Defines the probability of a gene being selected in the roulette of opt_roulette.
			opt_path_swap_it = Defines the number of simulations in the path optimizer.
			tx_elite = Defines the elitism rate in the population.
			verbose = Defines whether to activate the verbose.
			simple_verbose = Defines whether or not to activate the simple_verbose.
			alpha = Percentage of the parent gene relative to the mother's gene.
			balance = Defines in relation to the good percentage of the population that will be used for the new generation (0 defines as no elitism for generation).
			tx_mutation_AHCAVG = Defines the mutation rate in the arithmetic_average.
			fix_init = Defines whether there will be an initial number as fixed (-1 defines as not existing).
			cross_active = Stores which crossovers are active ("BCR" -> Best Cost Route crossover, "AHCAVG" -> Arithmetic Average, "CX" -> Cycle Crossover).
	*/

	int max_generations;
	int max_population;
	int swap_rate;
	bool roulette;
	int opt_path_swap_it;
	int tx_elite;
	bool verbose;
	bool simple_verbose;
	int alpha;
	int balance;
	int tx_mutation_AHCAVG;
	int fix_init;
	vector<string> cross_active;

	GA_Params()
	{
		tx_elite = 10;
		verbose = 0;
		simple_verbose = 1;
		fix_init = -1;
		max_generations = 10000;
		max_population = 100;
		verbose = false;
		tx_mutation_AHCAVG = 20;
		balance = 0;
		roulette = true;
		swap_rate = 40;
		opt_path_swap_it = 50;
		alpha = 50;
		cross_active = { "BCR", "AHCAVG","CX" };
	}


	void cross_active_delete(string code)
	{
		auto idx = find(cross_active.begin(), cross_active.end(), code);
		if (idx != cross_active.end())
			cross_active.erase(idx);
	}

	void cross_active_insert(string code)
	{
		auto idx = find(cross_active.begin(), cross_active.end(), code);
		if (idx == cross_active.end())
			cross_active.erase(idx);
	}
};

struct params
{
	bool genetic;
	GA_Params ga_p;

	params()
	{
		genetic = 1;
	}

	params(ifstream control_params)
	{
		string in_param;
		int value;
		while (control_params >> in_param)
		{
			if (in_param == "genetic")
			{
				int value;
				control_params >> value;
				genetic = value;
				continue;
			}

			if (in_param == "genetic.max_generations")
			{
				control_params >> value;
				if (value > 0)
				{
					ga_p.max_generations = value;
				}
				continue;
			}

			if (in_param == "genetic.max_population")
			{
				control_params >> value;
				if (value > 0)
				{
					ga_p.max_population = value;
				}
				continue;
			}

			if (in_param == "genetic.swap_rate")
			{
				control_params >> value;
				if (value >= 0)
				{
					ga_p.swap_rate = value;
				}
				continue;
			}

			if (in_param == "genetic.roulette")
			{
				control_params >> value;
				ga_p.swap_rate = value;
				continue;
			}

			if (in_param == "genetic.opt_path_swap_it")
			{
				control_params >> value;
				if (value >= 0)
				{
					ga_p.opt_path_swap_it = value;
				}
				continue;
			}

			if (in_param == "genetic.simple_verbose")
			{
				control_params >> value;
				ga_p.simple_verbose = value;
				continue;
			}

			if (in_param == "genetic.alpha")
			{
				control_params >> value;
				if (ga_p.balance >= 0 and ga_p.balance <= 100)
				{
					ga_p.alpha = value;
				}
				continue;
			}

			if (in_param == "genetic.balance")
			{
				control_params >> value;
				if(ga_p.balance >= 0 and ga_p.balance <= 100)
					ga_p.balance = value;
				
				continue;
			}

			if (in_param == "genetic.tx_mutation_AHCAVG")
			{
				control_params >> value;
				if(ga_p.tx_mutation_AHCAVG >=0)
					ga_p.tx_mutation_AHCAVG = value;
				continue;
			}

			if (in_param == "genetic.fix_init")
			{
				control_params >> value;
				ga_p.fix_init = value;
				continue;
			}

			if (in_param == "genetic.cross_active.BCR")
			{
				control_params >> value;
				if (value == 0)
				{
					ga_p.cross_active_delete("BCR");
				}
				else
				{
					ga_p.cross_active_insert("BCR");
				}
				continue;
			}

			if (in_param == "genetic.cross_active.AHCAVG")
			{
				control_params >> value;
				if (value == 0)
				{
					ga_p.cross_active_delete("AHCAVG");
				}
				else
				{
					ga_p.cross_active_insert("AHCAVG");
				}
				continue;
			}

			if (in_param == "genetic.cross_active.CX")
			{
				control_params >> value;
				if (value == 0)
				{
					ga_p.cross_active_delete("CX");
				}
				else
				{
					ga_p.cross_active_insert("CX");
				}
				continue;
			}
		}
	}
	
} param;