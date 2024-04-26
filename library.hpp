#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h> 
#include <fstream>
#include <algorithm>
#include <vector>
#include <math.h>

#define PARAMS_FILE "params.txt"
#define INPUT_FILE "input.txt"
#define LL long long
#define ULL unsigned long long
#define LD long double
#define INF 1e16

using namespace std;

struct annealing_params{
	/*
        Objective:
            A struct responsible for storing parameters for the annealing algorithm.

        Attributes:
            t0 - Initial temperature
            tf - Final temperature
            l - Number of iterations (exchanges) to be performed on the current solution
            alfa - Temperature variation rate
    */

	LD t0;
    LD tf;
    int l;
    LD alfa;

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
	int roulette;
	int opt_path_swap_it;
	int tx_elite;
	bool verbose;
	bool simple_verbose;
	int alpha;
	int balance;
	int tx_mutation_AHCAVG;
	int fix_init;
	vector<string> cross_active;
	int number_active_cross;

	GA_Params()
	{
		tx_elite = 7;
		verbose = 0;
		simple_verbose = 1;
		fix_init = -1;
		max_generations = 50000;
		max_population = 100;
		verbose = false;
		tx_mutation_AHCAVG =  20;
		balance = 0;
		roulette = 60;
		opt_path_swap_it = 50;
		alpha = 70;
		cross_active = { "BCR", "AHCAVG","CX" };
		number_active_cross = 3;
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

class params
{
	/*
		Objective:
			This structure is responsible for storing the parameters of the selected algorithm and the settings related to its execution.

		Attributes:
			genetic = Indicate whether the algorithm to be used is genetic or not.
			ga_p = Contains the specific parameters of the genetic algorithm.
	*/
public:
	bool genetic;
	GA_Params ga_p;

	params()
	{
		genetic = true;
	}

	params(string source)
	{
		/*
			Objective:
				An alternate constructor that allows initializing the parameters from a text file.
		*/

		ifstream control_params(source);
		string in_param;
		control_params >> in_param;

        if (in_param == "genetic") {
            genetic = true;
            params::genetic_params(control_params);
        }
		
	}
	
	void genetic_params(ifstream& control_params){

		string in_param;
		control_params >> in_param;
		int value;

		while (control_params >> in_param)
		{
			if(in_param == "genetic.tx_elite")
			{
				control_params >> value;
				if(value > 0 and value < 101)
					ga_p.tx_elite = value;
				continue;
			}

			if (in_param == "genetic.max_generations")
			{
				control_params >> value;
				if (value > 0)
					ga_p.max_generations = value;
				continue;
			}

			if (in_param == "genetic.max_population")
			{
				control_params >> value;
				if (value >= 10)
					ga_p.max_population = value;
				continue;
			}

			if (in_param == "genetic.roulette")
			{
				control_params >> value;
				if (ga_p.roulette >= 0 and ga_p.roulette <= 100)
					ga_p.roulette = value;
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
			
			if (in_param == "genetic.verbose")
			{
				control_params >> value;
				ga_p.verbose = value;
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
				if (ga_p.balance >= 0 and ga_p.balance <= 100)
					ga_p.balance = value;

				continue;
			}

			if (in_param == "genetic.tx_mutation_AHCAVG")
			{
				control_params >> value;
				if (ga_p.tx_mutation_AHCAVG >= 0 and ga_p.tx_mutation_AHCAVG <= 100)
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

		ga_p.tx_elite = (ga_p.tx_elite*ga_p.max_population)/100;
		ga_p.number_active_cross = ga_p.cross_active.size();
	}
};


struct point {
	/*
		Objective:
			A structure to represent a point in the Cartesian plane with coordinates X and Y.
	*/

	LD X, Y;
	point(LD x, LD y) : X(x), Y(y) {}
};


class utilities
{
	/*
		Objective:
			Class with useful functions.
	*/

public:
	static params param;
	static int n_cities;
	static vector<point> city;

	static LD euclidian_distance(point a, point b)
	{
		/*
			Objective:
				Calculate the Euclidean distance between two points.
		*/

		return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
	}

	static LD Fx_fit(vector<int> path, int n, vector<bool> contain)
	{
		/*
			Objective:
				Calculate the fitness value of a path (represented by a vector of points) based on the total distance traveledm and contain (vector<bool>) what indicates whether element i is active.
		*/

		LD fit = 0;

		for (int i = 0; i < n - 1; i++)
		{
			fit += utilities::euclidian_distance(city[path[i]], city[path[i + 1]]);
		}

		fit += utilities::euclidian_distance(city[path[n-1]], city[path[0]]);

		for (int i = 0; i < n; i++)
		{
			if (!contain[i])
			{

				fit = INF - fit;
				return fit;
			}
		}

		return fit;
	}

	static LD Fx_fit(vector<int> path, int n)
	{
		/*
			Objective:
				Calculate the fitness value of a path (represented by a vector of points) based on the total distance traveled.
		*/

		LD fit = 0;

		for (int i = 0; i < n - 1; i++)
		{
			fit += utilities::euclidian_distance(city[path[i]], city[path[i + 1]]);
		}

		fit += utilities::euclidian_distance(city[path[n-1]], city[path[0]]);

		return fit;
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

		if (range > 0)
			return start + rand() % range;

		return start;
	}

	static void input_points(string source = INPUT_FILE)
	{
		ifstream input(source);
		int n;
		input >> n;
		n_cities = n;
		while (n--)
		{
			LD x, y;
			input >> x >> y;
			city.push_back(point(x, y));
		}
	}
};