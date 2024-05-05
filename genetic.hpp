#pragma once
#include "library.hpp"
#include "ACO.hpp"
class gene
{
	/* 
		Objective:
			Represents a gene in a genetic algorithm.

		Attributes:
			nodes: Number of nodes in the gene.
			fit: Fitness value of the gene.
			path: Vector storing the current path of the gene.
			repath: Vector storing the index of each city in the path.
			contain: Vector indicating whether a city is included in the path.
	*/

public:
	int nodes;
	LD fit = 0;
	vector<int> path, repath;
	vector<bool> contain;

	gene(int n)
	{
		/*
			Objective:
				Constructor for the gene class.
			Parameters:
				- n: Number of nodes in the gene.
		*/

		nodes = n;
		path.assign(n, -1);
		repath.assign(n, -1);
		contain.assign(n, 0);
	}

	void bcr(gene& child, const gene& mother)
	{
		/* Best Cost Route crossover
			Objective:
				Perform crossover using the Best Cost Route method.
			Parameters:
				- child: Gene representing the child after crossover.
				- mother: Gene representing the mother gene.
		*/

		child = *this;
		vector<int> new_path;
		unordered_set<int> cut;
		
		if(utilities::random_range()%2 == 0)
		{
			child = mother;
			while (int(cut.size()) < nodes/2)
			{
				cut.insert(this->path[utilities::random_range((utilities::param.ga_p.fix_init == -1 ? 0 : utilities::param.ga_p.fix_init), nodes)]);
			}
		}
		else
		{
			while (int(cut.size()) < nodes/2)
			{
				cut.insert(mother.path[utilities::random_range((utilities::param.ga_p.fix_init == -1 ? 0 : utilities::param.ga_p.fix_init), nodes)]);
			}
		}
		
		for(auto e : cut)
		{
			new_path = child.path;
			new_path.erase(new_path.begin() + child.repath[e]);
			for(int i=(utilities::param.ga_p.fix_init == -1 ? 0 : 1); i<nodes; i++)
			{
				LD new_fit=INF;
				new_path.emplace(new_path.begin() + i, e);
				new_fit = utilities::Fx_fit(new_path, nodes,child.contain);

				if(new_fit < child.fit)
				{
					child.path = new_path;
					child.fit = new_fit;
				}
				new_path.erase(new_path.begin() + i);
			}
			
			child.contain.assign(nodes, 0);
			for (int i = 0; i < nodes; i++)
				child.repath[child.path[i]] = i, child.contain[child.path[i]] = 1;

		}
	}

	void vr(gene& child, const vector<gene>& genes)
	{	
		/* Voting Recombination Crossover
			Objective:
				Perform crossover using the Voting Recombination method.
			Parameters:
				- child: Gene representing the child after crossover.
				- genes: Vector of genes for voting.
		*/

		int i = 0;

		if (utilities::param.ga_p.fix_init != -1)
		{
			i = 1;
			child.insert(0, utilities::param.ga_p.fix_init); 
		}


		for(; i<nodes; i++)
		{
			vector<int> aux(nodes+1, utilities::param.ga_p.P_limiar);
			
			for(int j=utilities::param.ga_p.P_value-1; j>-1; j--)
			{
				aux[genes[j].path[i]]--;
				if(!aux[genes[j].path[i]] && child.not_repeat_insert(i,genes[j].path[i]))
					break;
			}
		}

		for (i=0; i<nodes; i++)
		{
			if(child.path[i] == -1)
				while(!child.not_repeat_insert(i,utilities::random_range(0, nodes)));
		}

		child.fit = utilities::Fx_fit(child.path, nodes, child.contain);
	}

	void arithmetic_average(gene& child, const gene& mother)
	{
		/* Arithmetic Average
			Objective:
				Perform crossover using the Arithmetic Average method.
			Parameters:
				- child: Gene representing the child after crossover.
				- mother: Gene representing the mother gene.
		*/

		int father_gene = ((100 - utilities::param.ga_p.tx_mutation_AHCAVG) *  utilities::param.ga_p.alpha) / 100;
		int rate = utilities::random_range(0, 100);

		if (utilities::param.ga_p.fix_init != -1 or rate <= father_gene)
		{
			child.insert(0, this->path[0]);
		}
		else
		{
			if (rate <=  100 - father_gene)
			{
				child.insert(0, mother.path[0]);
			}
			else
			{
				child.insert(0, utilities::random_range(0, nodes));
			}
		}

		for (int i = 1; i < nodes; i++)
		{
			rate = utilities::random_range(0, 100);

			if (rate <= father_gene)
			{
				child.insert(i, this->path[i]);
			}
			else
			{
				if (rate <=  100 - father_gene)
				{
					child.insert(i, mother.path[i]);
				}
				else
				{
					child.insert(i, utilities::random_range(0, nodes));
				}
			}
		}

		child.fit = utilities::Fx_fit(child.path, nodes, child.contain);
	}

	void pmx(gene& child, const gene& mother)
	{ 
		/* PMX Crossover
			Objective:
				Perform crossover using the PMX method.
			Parameters:
				- child: Gene representing the child after crossover.
				- mother: Gene representing the mother gene.
		*/

		int idx = utilities::random_range(0, nodes);
		int idy = idx;

		while(abs(idx - idy) <= 2)
			idy = utilities::random_range(0, nodes);

		if(idx>idy)
			swap(idx, idy);
		
		for(int i=idx; i<=idy; i++)
			child.insert(i, this->path[i]);

		for(int i=idx; i<=idy; i++)
		{
			if (!child.contain[mother.path[i]])
			{
				int find = mother.path[i];
				int index = i;
				while (index >= idx && index<=idy)
				{						
					find = this->path[index];
					index = mother.repath[find];
				}
				child.insert(index, mother.path[i]);
			}
		}

		for(int i=0; i<nodes; i++)
		{
			if(child.path[i] == -1)
				child.insert(i, mother.path[i]);
		}

		child.fit = utilities::Fx_fit(child.path, nodes, child.contain);
	}
	
	void er(gene& child, const gene& mother)
	{
		/* Edge Recombination crossover
			Objective:
				Perform crossover using the Edge Recombination method.
			Parameters:
				- child: Gene representing the child after crossover.
				- mother: Gene representing the mother gene.
		*/

		vector<set<int>> adj(nodes);
		int cont=0;
		child.insert(cont, (utilities::random_range()%2 ? mother.path[0] : this->path[0]));
		
		for(int i=0; i<nodes; i++)
		{
			adj[this->path[i]].insert((i+1<nodes ? this->path[i+1] : this->path[0]));
			adj[this->path[i]].insert((i-1>-1 ? this->path[i-1] : this->path[nodes-1]));
			adj[mother.path[i]].insert((i+1<nodes ? mother.path[i+1] : mother.path[0]));
			adj[mother.path[i]].insert((i-1>-1 ? mother.path[i-1] : mother.path[nodes-1]));
		}

		while(cont<nodes-1)
		{
			bool ok=0;
			for(auto e : adj[child.path[cont]])
			{
				if(child.not_repeat_insert(cont+1, e))
				{
					cont++;
					ok=1;
					break;
				}
			}

			while(!ok)
			{
				int item = utilities::random_range(0, nodes);
				if(child.not_repeat_insert(cont+1, item))
				{
					cont++;
					ok=1;
				}
			} 
		}

		child.fit = utilities::Fx_fit(child.path, nodes, child.contain);
	}
	
	void opt_path(bool mutation)
	{
		/*
			Objective:
				Update the path by simulating internal changes.
		*/

		for (int i = 0; i < utilities::param.ga_p.opt_path_swap_it; i++)
		{
			utilities::opt_2s(path, fit, mutation);
		}
	
		recalculation_repath();
	}

	gene cross(const gene& mother,const vector<gene>& genes)
	{
		/*
			Objective:
				Choose which crossover method to perform.
			Parameters:
				- mother: Gene representing the mother gene.
				- genes: Vector of genes for voting crossover.
			Returns:
				Gene representing the child after crossover.
		*/

		gene child(nodes);
		gene child_save(nodes);

		pmx(child, mother);
	
		if (utilities::random_range(0, 100)  < utilities::param.ga_p.cross_active[0])
		{
			bcr(child_save, mother);

			if (child_save.fit < child.fit)
				child = child_save;

			child_save = gene(nodes);
		}

		if (utilities::param.ga_p.cross_active[2])
		{
			er(child_save, mother);

			if (child_save.fit < child.fit)
				child = child_save;

			child_save = gene(nodes);
		}

		if (utilities::param.ga_p.cross_active[3])
		{
			vr(child_save, genes);

			if (child_save.fit < child.fit)
				child = child_save;
		}

		return child;

	}

	void recalculation_repath()
	{
		/*
			Objective:
				Recalculate the repath vector based on the current path vector.
		*/

		for (int i = 0; i < nodes; i++)
			this->repath[this->path[i]] = i;
	}


	void mutation_swap(bool mutation)
	{
		/*
			Objective:
				Perform mutation by swapping two random indices in the gene.
		*/

		utilities::opt1(path, fit, mutation);

		opt_path(mutation);
	}

	bool not_repeat_insert(const int& i, const int& x)
	{
		/*
			Objective:
				Insert an item at position i in the gene, avoiding repetition.
			Parameters:
				- i: Index at which to insert the item.
				- x: Item to be inserted.
			Returns:
				True if the item was inserted successfully, false otherwise.
		*/

		if (contain[x])
			return false;

		contain[x] = true;
		path[i] = x;
		repath[x] = i;
		return true;
	}

	void insert(const int& i, const int& x)
	{
		/*
			Objective:
				Insert an item at position i in the gene.
			Parameters:
				- i: Index at which to insert the item.
				- x: Item to be inserted.
		*/

		contain[x] = true;
		path[i] = x;
		repath[x] = i;
	}
};

bool order(const gene& a,const gene& b)
{
	
	/*
		Objective:
			Function with the logic used to order genes.
	*/

	return a.fit< b.fit;
}

class genetic
{
	
	/*
		Objective:
			Class with the objective of executing the heuristics algorithm.
	*/

	int population;
	int n_cities;
	vector<gene> genes;
	bool _active = false;

	void calculate_relative_fit(vector<LD>& relative_fitness, LD& max_probability)
	{
		/*
			Objective:
				Function to calculate the relative fit to be used in the roulette method.
		*/

		LD max_fitness = INF;
		max_probability = 0;

		for (int i = 0; i < utilities::param.ga_p.max_population; i++)
		{
			LD relative_fit = max_fitness - genes[i].fit;
			relative_fitness.push_back(relative_fit);
			max_probability += relative_fit;
		}
	}

	void roulette_wheel_selection(int& father, int& mother)
	{
		/*
			Objective:
				Function to choose all genes using the roulette wheel method.
		*/

		LD max_probability = 0;
		vector<LD> relative_fitness;

		calculate_relative_fit(relative_fitness, max_probability);

		LD random_value = utilities::random_range_double(0, max_probability);
		LD cumulative_probability = 0;

		for (int i = 0; i < utilities::param.ga_p.max_population; i++)
		{
			cumulative_probability += relative_fitness[i];
			if (random_value <= cumulative_probability)
			{
				father = i;
				break;
			}
		}

		if (father == -1)
		{
			father = utilities::random_range(0, utilities::param.ga_p.max_population);
		}

		random_value = utilities::random_range_double(0, max_probability);
		cumulative_probability = 0;

		for (int i = 0; i < utilities::param.ga_p.max_population; i++)
		{
			cumulative_probability += relative_fitness[i];
			if (random_value <= cumulative_probability)
			{
				mother = i;
				break;
			}
		}

		if (mother == -1)
		{
			mother = utilities::random_range(0, utilities::param.ga_p.max_population);
		}

		while (mother == father)
			mother = utilities::random_range(0, utilities::param.ga_p.max_population);
	}

	void tournament_selection(int& father, int& mother)
	{
		/*
			Objective:
				Function to choose two individuals using tournament selection method.
		*/

		const int tournament_size = min(5, population); 
		vector<int> tournament_contestants(tournament_size);

		for (int i = 0; i < tournament_size; ++i)
		{
			tournament_contestants[i] = utilities::random_range(0, utilities::param.ga_p.max_population);
		}

		int tournament_winner = tournament_contestants[0]; 
		for (int i = 1; i < tournament_size; ++i)
		{
			if (genes[tournament_contestants[i]].fit > genes[tournament_winner].fit)
			{
				tournament_winner = tournament_contestants[i];
			}
		}

		father = tournament_winner; 

		for (int i = 0; i < tournament_size; ++i)
		{
			tournament_contestants[i] = utilities::random_range(0, utilities::param.ga_p.max_population);
		}

		tournament_winner = tournament_contestants[0]; 
		for (int i = 1; i < tournament_size; ++i)
		{
			if (genes[tournament_contestants[i]].fit > genes[tournament_winner].fit)
			{
				tournament_winner = tournament_contestants[i];
			}
		}

		mother = tournament_winner; 
	}

	void simulation()
	{
		/*
			Objective:
				Function with the objective of simulating the generations of the algorithm, choosing between the active crossover types and optimizers.
		*/
	
		int it = 1;

		while(it <= utilities::param.ga_p.max_generations)
		{	
			sort(genes.begin(), genes.end(), order);
			
			seed = std::chrono::system_clock::now().time_since_epoch().count();
			gen = mt19937 (seed);

			if(utilities::param.ga_p.verbose == 1 && it%10==0)
				print_verbose(it/10);

			vector<gene> new_generation(population, gene(n_cities));

			for (int i = 0; i <  utilities::param.ga_p.tx_elite; i++)
			{
				new_generation[i] = genes[i];
				new_generation[i].mutation_swap(false);
			}

			for (int i =  utilities::param.ga_p.tx_elite; i < population; i++)
			{
				int father = -1, mother = -1;
				
				if(utilities::param.ga_p.balance > 0)
				{
					father = utilities::random_range(0,  population /  utilities::param.ga_p.balance);
					mother = utilities::random_range(0, population /  utilities::param.ga_p.balance);
				}
				else
				{
					if(utilities::random_range()%2 == 0)
						roulette_wheel_selection(father, mother);
					else
						tournament_selection(father, mother);
				}
				
				new_generation[i] = genes[father].cross(genes[mother], genes);
			}

			for(int i=utilities::param.ga_p.tx_elite; i<population; i++)
			{
				if(utilities::random_range(0, 100) < utilities::param.ga_p.opt_range)
				{
					if(utilities::random_range()%2 == 0)
						utilities::opt_2s(new_generation[i].path, new_generation[i].fit, true);
					else
						utilities::opt1(new_generation[i].path, new_generation[i].fit, true);

					new_generation[i].recalculation_repath();
				}
				else
					new_generation[i].mutation_swap(false);
			}
			
			genes = new_generation;
			it++;
		}
	}

	void init()
	{
		/*
			Objective:
				Function to initialize the gene vector with allowed paths.
		*/

		for (int i = 0; i < population; i++)
		{
			if (utilities::param.ga_p.fix_init == -1)
				utilities::random_path(utilities::random_range(0, utilities::n_cities), 0, genes[i].fit, genes[i].path, genes[i].repath, genes[i].contain);			
			else
				utilities::random_path(utilities::param.ga_p.fix_init, 0, genes[i].fit, genes[i].path, genes[i].repath, genes[i].contain);	
		}
	}
	
	void print_verbose(const int& x)
	{
		/*
			Objective:
				Function to print the best current fit and the path of this gene.
		*/

		cout << "Generation " << x << ":\n";
		cout << "Best: " << genes[0].fit << " cust\n";
		
		if ( utilities::param.ga_p.simple_verbose == 0)
		{
			cout << "Current Population: \n";
			for (auto e : genes)
			{
				cout << "Best: " << e.fit << " cust\n";
				cout << "Path: ";
				for (int i = 0; i < n_cities; i++)
				{
					cout << e.path[i];
					if (i + 1 < n_cities)
					{
						cout << " ";
					}
				}
				cout << endl;
			}
		}
	}

public:
	genetic(int number_of_cities) 
	{
		/*
			Objective:
				Genetic class constructor.
		*/

		n_cities = number_of_cities;
		population =  utilities::param.ga_p.max_population;
		genes.assign(population,gene(n_cities));
	}

	LD best_fit()
	{
		/*
			Objective:
				Function that returns the best fit found.
		*/

		if(!_active)
		{
			return INF;
		}

		return genes[0].fit;
	}

	vector<vector<int>> current_all_path()
	{
		/*
			Objective:
				Function that returns the current genes.
		*/

		vector<vector<int>> all_path;
		
		for (auto e:genes)
		{
			all_path.push_back(e.path);
		}

		return all_path;
	}

	vector<int> best_path()
	{
		/*
			Objective:
				Function that returns the path with the best fit.
		*/

		if(!_active)
		{
			return vector<int>(0);
		}

		return genes[0].path;
	}

	LD activate()
	{
		/*
			Objective:
				Function with the aim of activating the genetic algorithm.
		*/

		init();
		simulation();
		sort(genes.begin(), genes.end(), order);
		_active = true;
		return genes[0].fit;
	}
};