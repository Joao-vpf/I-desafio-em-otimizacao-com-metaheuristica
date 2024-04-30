#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <random>
#include <fstream>
#include <cstdlib>
#include <chrono>
#include <limits.h>
#include <algorithm>
#include <vector>
#include <set>
#include <math.h>

#define PARAMS_FILE "params.txt"
#define BEST_PARAMS_FILE "best_params.txt"
#define INPUT_FILE "input.txt"
#define LL long long
#define ULL unsigned long long
#define LD double
#define INF 1e16

using namespace std;

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

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

	LD t0 = 100000;
    LD tf = 0.001;
    int l = 100000;
    LD alfa = 0.05;

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
			P_value = Defines how many parents were considered.
			P_limiar = Defines the minimum quantity required for the city and to appear in the same position as the parents.
			VR = Boolean that indicates whether the Voting Recombination Crossover is active.
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
	int P_value;
	int P_limiar;
	bool VR;
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
		P_value = 4;
		P_limiar = 3;
		VR = 1;
		opt_path_swap_it = 50;
		alpha = 70;
		cross_active = { "BCR", "AHCAVG","CX", "VR", "ER"};
		number_active_cross = 5;
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

struct ABC_Params
{
	int max_population;
	int max_generations;
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
	vector<bool> hybrid;
	annealing_params ann_p;
	GA_Params ga_p;

	params()
	{
		hybrid.assign(2, 0);
	}

	params(string source)
	{
		/*
			Objective:
				An alternate constructor that allows initializing the parameters from a text file.
		*/

		hybrid.assign(2, 0);
		ifstream control_params(source);
		string in_param;

		while(control_params >> in_param)
		{
			if (in_param == "genetic") 
			{
				hybrid[0] = true;
				params::genetic_params(control_params);
			}

			if(in_param == "annealing")
			{
				hybrid[1] = true;
			}
		}
	}
	
	void genetic_params(ifstream& control_params){

		string in_param;
		int value;

		while (control_params >> in_param && in_param != "end")
		{
			if(in_param == "genetic.tx_elite")
			{
				control_params >> value;
				if(value > 1 and value < 101)
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
				if (ga_p.balance >= 0 and ga_p.balance < 4)
					ga_p.balance = value;

				continue;
			}

			if (in_param == "genetic.tx_mutation_AHCAVG")
			{
				control_params >> value;
				if (ga_p.tx_mutation_AHCAVG >= 0 and ga_p.tx_mutation_AHCAVG < 100)
					ga_p.tx_mutation_AHCAVG = value;
				continue;
			}

			if (in_param == "genetic.fix_init")
			{
				control_params >> value;
				ga_p.fix_init = value;
				continue;
			}

			if (in_param == "genetic.P_value")
			{
				control_params >> value;
				if(ga_p.P_value > 1)
					ga_p.P_value = value;
				continue;
			}

			if (in_param == "genetic.P_limiar")
			{
				control_params >> value;
				if (value > 0)
					ga_p.P_limiar = value;
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

			if (in_param == "genetic.cross_active.VR")
			{
				control_params >> value;
				if (value == 0)
				{
					ga_p.VR = 0;
					ga_p.cross_active_delete("VR");
				}
				else
				{
					ga_p.VR = 1;
					ga_p.cross_active_insert("VR");
				}
				continue;
			}
			
			if (in_param == "genetic.cross_active.ER")
			{
				control_params >> value;
				if (value == 0)
				{
					ga_p.cross_active_delete("ER");
				}
				else
				{
					ga_p.cross_active_insert("ER");
				}
				continue;
			}
		}
		
		ga_p.P_value = min(ga_p.P_value, ga_p.max_population);
		ga_p.P_limiar = min(ga_p.P_limiar, ga_p.P_value);
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
	
	static void random_path(const int& initial,const bool& reapeat, LD& fit, vector<int>& path, vector<bool>& contain)
	{
		/*
			Objective:
				Method that creates a random path.
		*/

		path[0] = initial;
		contain[initial] = 1;
		
		for (int i = 1; i < n_cities; i++)
		{
			int idx = utilities::random_range(0, n_cities);
			
			while (!reapeat && contain[idx])
			{
				idx = utilities::random_range(0, n_cities);
			}

			path[i] = idx;
			contain[idx] = 1;
		}
		fit = Fx_fit(path, n_cities, contain);
	}

	static void random_path(const int& initial,const bool& reapeat, LD& fit, vector<int>& path, vector<int>& repath, vector<bool>& contain)
	{
		/*
			Objective:
				Method that creates a random path.
		*/

		path[0] = initial;
		repath[initial] = 0;
		contain[initial] = 1;
		
		for (int i = 1; i < n_cities; i++)
		{
			int idx = utilities::random_range(0, n_cities);
			
			while (!reapeat && contain[idx])
			{
				idx = utilities::random_range(0, n_cities);
			}

			path[i] = idx;
			repath[idx] = i;
			contain[idx] = 1;
		}
		fit = Fx_fit(path, n_cities, contain);
	}

	static LD euclidian_distance(const point& a, const point& b)
	{
		/*
			Objective:
				Calculate the Euclidean distance between two points.
		*/

		return sqrt((a.X - b.X) * (a.X - b.X) + (a.Y - b.Y) * (a.Y - b.Y));
	}

	static LD Fx_fit(const vector<int>& path, const int& n, const vector<bool>& contain)
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

	static LD Fx_fit(const vector<int>& path, const int& n)
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

	static int random_range(int start=0, int end=INT_MAX)
	{
		/*
			Objective:
				Find a random number between the start and end (excluding the end).
		*/

		if(start > end) 
			swap(start, end);
		
		uniform_int_distribution<> dis(start, end-1);
		return dis(gen);
	}

	static LD random_range_01()
	{
		/*
			Objective:
				Find a random number between the 0 and 1.
		*/

		uniform_int_distribution<> dis(0, 100);
		int value_gen = dis(gen); 
		
		if(!value_gen)
			return 0;

		return 100/dis(gen);
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