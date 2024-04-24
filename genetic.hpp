#pragma once
#include "library.hpp"

class gene
{
	void bcr(gene& child, gene mother)
	{//Best Cost Route crossover
		int cut = utilities::random_range(1, nodes);

		for (int i = 0; i < cut; i++)
		{
			child.insert(i, this->path[i]);
		}

		for (int i = 0; i < nodes && cut < nodes; i++)
		{
			if (!child.contain[mother.path[i]])
			{
				child.insert(cut++, mother.path[i]);
			}
		}

		while (cut < nodes)
		{
			int microgene_mutant = utilities::random_range(0, nodes);
			if (!child.contain[microgene_mutant])
			{
				child.insert(cut++, microgene_mutant);
			}
		}

		child.fit = utilities::Fx_fit(child.path, nodes, child.contain);
	}

	void arithmetic_average(gene& child, gene mother)
	{//arithmetic_average

		int father_gene =  utilities::param.ga_p.tx_mutation_AHCAVG *  utilities::param.ga_p.alpha / 100;
		int rate = utilities::random_range(0, 100);

		if (utilities::param.ga_p.fix_init != -1 or rate <= father_gene)
		{
			child.insert(0, this->path[0]);
		}
		else
		{
			if (rate <=  100-utilities::param.ga_p.tx_mutation_AHCAVG)
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
				if (rate <=  100-utilities::param.ga_p.tx_mutation_AHCAVG)
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
	

	void cx(gene& child, gene mother)
	{ //Cycle Crossover
		gene bastard(nodes);
		bastard.random_path(mother.path[0]);
		child.random_path(this->path[0]);
		vector<vector<int>> cycles;
		vector<bool> visited(nodes + 1, false);

		for (int i = 0; i < nodes; ++i)
		{
			if (!visited[this->path[i]])
			{
				vector<int> cycle = { static_cast<int>(i) };
				visited[this->path[i]] = true;

				int j = mother.repath[this->path[i]];
				if (j == -1)
				{
					continue;
				}
				while (j != cycle[0] and !visited[j])
				{
					cycle.push_back(j);
					visited[j] = true;
					j = mother.repath[this->path[j]];
					if (j == -1)
					{
						break;
					}
				}
				cycles.push_back(cycle);
			}
		}

		size_t cycle_index = 0;
		for (auto& cycle : cycles)
		{
			for (auto u : cycle)
			{
				if (cycle_index % 2 == 0)
				{
					child.insert(u, this->path[u]);
					bastard.insert(u, mother.path[u]);
				}
				else
				{
					child.insert(u, mother.path[u]);
					bastard.insert(u, this->path[u]);
				}
			}
			cycle_index++;
		}

		bastard.fit = utilities::Fx_fit(bastard.path, bastard.nodes, bastard.contain);
		child.fit = utilities::Fx_fit(child.path, child.nodes, child.contain);

		if (child.fit > bastard.fit)
		{
			child = bastard;
		}
	}
	

	void opt_path()
	{
		for (int i = 0; i < utilities::param.ga_p.opt_path_swap_it; i++)
		{
			vector<int> path_copy = path;
			int idxA = utilities::random_range(1, nodes - 2);
			int idxB = utilities::random_range(1, nodes - 2);

			while (idxB == idxA)
				idxB = utilities::random_range(1, nodes - 2);

			if (idxA > idxB)
				swap(idxA, idxB);

			while (idxA < idxB)
			{
				swap(path_copy[idxA], path_copy[idxB]);
				idxA++;
				idxB--;
			}
			
			LD cust_copy = utilities::Fx_fit(path_copy, nodes, contain);
			if (cust_copy < this->fit)
			{
				path = path_copy;
				utilities::Fx_fit(this->path, this->nodes, this->contain);
			}
		}
	}

public:
	int nodes;
	LD fit = 0;
	vector<int> path, repath;
	vector<bool> contain;

	gene(int n)
	{
		nodes = n;
		path.assign(n, -1);
		repath.assign(n, -1);
		contain.assign(n, 0);
	}

	void random_path(const int& initial)
	{
		path[0] = initial;
		repath[initial] = 0;
		contain[initial] = 1;
		for (int i = 1; i < nodes; i++)
		{
			int idx = utilities::random_range(0, nodes);
			while (contain[idx])
			{
				idx = utilities::random_range(0, nodes);
			}
			path[i] = idx;
			repath[idx] = i;
			contain[idx] = 1;
		}
		utilities::Fx_fit(this->path, this->nodes, this->contain);
	}

	gene operator + (gene mother)
	{
		gene child(nodes);
		int idx = utilities::random_range(0,  utilities::param.ga_p.number_active_cross);
		
		if (idx == -1)
			return 0;

		string cross =  utilities::param.ga_p.cross_active[idx];
		
		if (cross == "BCR")
			bcr(child, mother);
		
		if (cross == "AHCAVG")
			arithmetic_average(child, mother);

		if (cross == "CX")
			cx(child, mother);
			
		return child;
	}
		
	void mutation_swap()
	{
		int idxA = utilities::random_range(1, nodes - 2);
		int idxB = utilities::random_range(1, nodes - 2);
		swap(this->path[idxA], this->path[idxB]);
		utilities::Fx_fit(this->path,this->nodes, this->contain);
		opt_path();
	}

	bool not_repeat_insert(int i, int x)
	{
		if (contain[x])
			return false;

		contain[x] = true;
		path[i] = x;
		repath[x] = i;
		return true;
	}

	void insert(int i, int x)
	{
		contain[x] = true;
		path[i] = x;
		repath[x] = i;
	}
};

bool order(const gene& a,const gene& b)
{
	return a.fit< b.fit;
}

class genetic
{
	int population;
	int n_cities;
	vector<gene> genes;

	
	vector <LD> calculate_relative_cust()
	{
		LD max_fitness = INF;

		vector<LD> relative_fitness;
		for (int i = 0; i < utilities::param.ga_p.max_population; i++) 
		{
			relative_fitness.push_back(max_fitness - genes[i].fit);
		}

		return relative_fitness;
	}


	void roulette_wheel_selection(int& father, int& mother)
	{
		ULL random_value = rand();
		ULL cumulative_probability = 0;
		vector<LD> relative_fitness = calculate_relative_cust();
		
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
			father =  utilities::random_range(0, utilities::param.ga_p.max_population);
		}

		random_value = rand();

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
			mother =  utilities::random_range(0, utilities::param.ga_p.max_population);
		}
		
		while(mother == father)
			mother = utilities::random_range(0, utilities::param.ga_p.max_population);

	}

	void simulation()
	{
	
		for (int it = 1; it <= utilities::param.ga_p.max_generations; it++)
		{	
			sort(genes.begin(), genes.end(), order);
			vector<gene> new_generation(population, gene(n_cities));

			for (int i = 0; i <  utilities::param.ga_p.tx_elite; i++)
			{
				new_generation[i] = genes[i];
			}

			for (int i =  utilities::param.ga_p.tx_elite; i < population; i++)
			{
				int father = -1, mother = -1;
				if(utilities::param.ga_p.balance > 0)
				{
					utilities::random_range(0,  n_cities /  utilities::param.ga_p.balance);
					utilities::random_range(0, n_cities /  utilities::param.ga_p.balance);
				}
				else
				{
					roulette_wheel_selection(father, mother);
				}
				new_generation[i] = genes[father] + genes[mother];
			}
			
			for (int i =  utilities::param.ga_p.tx_elite; i <  utilities::param.ga_p.max_population; i++)
			{
				int rate = utilities::random_range(0, 100);
				if (rate <= utilities::param.ga_p.roulette && new_generation[i].fit > genes[utilities::param.ga_p.tx_elite-1].fit)
				{
					new_generation[i].mutation_swap();
				}
			}

			genes = new_generation;

			if ( utilities::param.ga_p.verbose == 1 and it%1000 == 0)
			{
				print_verbose(it / 1000);
			}

		}
	}

	void init()
	{
		for (int i = 0; i < population; i++)
		{
			int j = 0;
			
			if(utilities::param.ga_p.fix_init!=-1)
				genes[i].not_repeat_insert(j, utilities::param.ga_p.fix_init), j++;

			while (j < n_cities)
			{
				int city = utilities::random_range(0, n_cities); 
				if (genes[i].not_repeat_insert(j, city))
				{
					j++;
				}
			}
			genes[i].fit = utilities::Fx_fit(genes[i].path, n_cities, genes[i].contain);
		}
	}
	
	void print_verbose(int x)
	{
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
		n_cities = number_of_cities;
		population =  utilities::param.ga_p.max_population;
		genes.assign(population,gene(n_cities));
	}

	LD activate()
	{
		init();
		simulation();
		sort(genes.begin(), genes.end(), order);
		return genes[0].fit;
	}
};