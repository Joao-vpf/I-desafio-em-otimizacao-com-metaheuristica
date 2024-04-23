#pragma once
#include "library.hpp"

class gene
{
	
	void bcr(gene* child, gene* mother)
	{//Best Cost Route crossover
		int cut = utilities::random_range(1, nodes);

		for (int i = 0; i < cut; i++)
		{
			child->insert(i, this->path[i]);
		}

		for (int i = 0; i < nodes and cut < nodes; i++)
		{
			if (!child->contain[mother->path[i]])
			{
				child->insert(cut++, mother->path[i]);
			}
		}

		while (cut < nodes)
		{
			int microgene_mutant = utilities::random_range(0, nodes);
			if (!child->repath[microgene_mutant])
			{
				child->insert(cut++, microgene_mutant);
			}
		}

		child->fit = utilities::Fx_fit(child->path, nodes, child->contain);
	}

	void arithmetic_average(gene* child, gene* mother)
	{//arithmetic_average

		int father_gene = param.ga_p.tx_mutation_AHCAVG * param.ga_p.alpha / 100;
		int rate = utilities::random_range(0, 100);

		if (param.ga_p.fix_init != -1 or rate <= father_gene)
		{
			child->insert(0, this->path[0]);
		}
		else
		{
			if (rate <= param.ga_p.tx_mutation_AHCAVG)
			{
				child->insert(0, mother->path[0]);
			}
			else
			{
				child->insert(0, utilities::random_range(0, nodes));
			}
		}

		for (int i = 1; i < nodes; i++)
		{
			rate = utilities::random_range(0, 100);

			if (rate <= father_gene)
			{
				child->insert(i, this->path[i]);
			}
			else
			{
				if (rate <= param.ga_p.tx_mutation_AHCAVG)
				{
					child->insert(i, mother->path[i]);
				}
				else
				{
					child->insert(i, utilities::random_range(0, nodes));
				}
			}
		}

		child->fit = utilities::Fx_fit(child->path, nodes, child->contain);
	}
	/*
	void cx(gene* child, gene* mother)
	{ //Cycle Crossover
		size_t nodes = mother.get_nodes();
		T bastard;
		bastard.init(nodes);
		bastard.random_gene(mother.get_microgene(0), matrix_adj);
		children.init(nodes);
		children.random_gene(father.get_microgene(0), matrix_adj);
		vector<vector<int>> cycles;
		vector<bool> visited(nodes + 1, false);

		for (size_t i = 0; i < nodes; ++i)
		{
			if (!visited[father.get_microgene(i)])
			{
				vector<int> cycle = { static_cast<int>(i) };
				visited[father.get_microgene(i)] = true;

				int j = mother.idx_microgene(father.get_microgene(i));
				if (j == -1)
				{
					continue;
				}
				while (j != cycle[0] and !visited[j])
				{
					cycle.push_back(j);
					visited[j] = true;
					j = mother.idx_microgene(father.get_microgene(j));
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
					children.insert_gene(u, father.get_microgene(u));
					bastard.insert_gene(u, mother.get_microgene(u));
				}
				else
				{
					children.insert_gene(u, mother.get_microgene(u));
					bastard.insert_gene(u, father.get_microgene(u));
				}
			}
			cycle_index++;
		}

		bastard.insert_gene(nodes, bastard.get_microgene(0));
		children.insert_gene(nodes, children.get_microgene(0));

		bastard.fx_cust(matrix_adj);
		children.fx_cust(matrix_adj);

		if (children.get_cust() > bastard.get_cust())
		{
			children = bastard;
		}
	}
	*/
public:
	int nodes;
	LL fit = 0;
	vector<int> path, repath;
	vector<bool> contain;

	gene(int n)
	{
		nodes = n;
		path.assign(n, -1);
		contain.assign(n, 0);
	}

	gene* operator + (gene* mother)
	{
		gene* child = new gene(nodes);
		int idx = utilities::random_range(0, param.ga_p.number_active_cross);
		
		if (idx == -1)
			return 0;

		string cross = param.ga_p.cross_active[idx];

		if (cross == "BCR")
			bcr(child, mother);
		
		//if (cross == "AHCAVG")
			
		return child;
	}
		
	void copy(gene* mother)
	{
		this->contain = mother->contain;
		this->repath = mother->repath;
		this->nodes = mother->nodes;
		this->path = mother->path;
		this->fit = mother->fit;
	}

	bool not_repeat_insert(int i, int x)
	{
		if (contain[x])
			return false;
	
		contain[x] = true;
		path[i] = x;
		repath[x] = i;
	}

	void insert(int i, int x)
	{
		contain[x] = true;
		path[i] = x;
		repath[x] = i;
	}
};

class genetic
{
	int population;
	int n_cities;
	vector<gene*> genes;

	bool order(gene* a, gene* b)
	{
		return a->fit > b->fit;
	}


	void simulation()
	{
		for (int it = 1; it <= population; it++)
		{

			sort(genes.begin(), genes.end(), order);
			vector<gene*> new_generation(population);

			for (int i = 0; i < param.ga_p.tx_elite; i++)
			{
				new_generation[i] = new gene(n_cities);
				new_generation[i]->copy(genes[i]);
			}

			for (int i = param.ga_p.tx_elite; i < population; i++)
			{
				int l = utilities::random_range(0, (param.ga_p.balance > 0 ? n / param.ga_p.balance : n));
				int r = utilities::random_range(0, (param.ga_p.balance > 0 ? n / param.ga_p.balance : n));
				new_generation[i] = genes[l] + genes[r];
			}


			if (param.ga_p.verbose == 1 and it%1000 == 0)
			{
				print_verbose(it / 1000 + 1);
			}
		}
	}

	void init()
	{
		for (int i = 0; i < population; i++)
		{
			genes[i] = new gene(n_cities);
			int j = 0; 
		}
	}
	
	void print_verbose(int x)
	{
		cout << "Generation " << x << ":\n";
		cout << "Best: " << genes[0]->fit << " cust\n";
		
		if (param.ga_p.simple_verbose == 0)
		{
			cout << "Current Population: \n";
			for (auto e : genes)
			{
				cout << "Best: " << e->fit << " cust\n";
				cout << "Path: ";
				for (int i = 0; i < population; i++)
				{
					cout << e->path[i];
					if (i + 1 < population)
					{
						cout << " -> ";
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
		population = param.ga_p.max_population;
		genes.assign(population,0);
	}

	LD activate()
	{
		init();
		simulation();
		sort(genes.begin(), genes.end(), order);
		return genes[0]->fit;
	}
};