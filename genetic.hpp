#pragma once
#include "library.hpp"

class gene
{
	vector<int> path;

	static void bcr(gene* mother)
	{//Best Cost Route crossover
		int nodes = mother.get_nodes();;
		children.init(nodes);

		int cut = random_range(1, nodes - 1);
		for (int i = 0; i < cut; i++)
		{
			children.insert_gene(i, father.get_microgene(i));
		}

		for (int i = 0; i < nodes and cut < nodes; i++)
		{
			if (!children.has_microgene(mother.get_microgene(i)))
			{
				children.insert_gene(cut++, mother.get_microgene(i));
			}
		}

		while (cut < nodes)
		{
			int microgene_mutant = random_range(0, nodes);
			if (!children.has_microgene(microgene_mutant))
			{
				children.insert_gene(cut++, microgene_mutant);
			}
		}

		children.insert_gene(nodes, children.get_microgene(0));
		children.fx_cust(matrix_adj);

	}

	static void arithmetic_average(gene* mother)
	{//arithmetic_average

		int father_gene = params_active_ga.tx_parents / params_active_ga.alpha, mom_gene = params_active_ga.tx_parents, nodes = mother.get_nodes();;
		children.init(nodes);

		int rate = random_range(0, 100);
		if (params_active_ga.fix != -1)
		{
			rate = random_range(0, mom_gene);
		}

		if (rate <= father_gene)
		{
			children.insert_gene(0, father.get_microgene(0));
		}
		else
		{
			if (rate <= mom_gene)
			{
				children.insert_gene(0, mother.get_microgene(0));
			}
			else
			{
				children.insert_gene(0, random_range(0, nodes));
			}
		}

		for (int i = 1; i < nodes; i++)
		{
			rate = random_range(0, 100);

			if (rate <= father_gene)
			{
				children.insert_gene(i, father.get_microgene(i));
			}
			else
			{
				if (rate <= mom_gene)
				{
					children.insert_gene(i, mother.get_microgene(i));
				}
				else
				{
					children.insert_gene(i, random_range(0, nodes));
				}
			}
		}

		children.insert_gene(nodes, children.get_microgene(0));
		children.fx_cust(matrix_adj);
	}

	static void cx(gene* mother)
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

public:
	LL fit = 0;
	gene* operator +(gene mother)
	{
		
	}

};

class genetic
{
	int n;
	vector<gene> genes;

	bool order(gene a, gene b)
	{
		return a.fit > b.fit;
	}

public:
	genetic() 
	{
		n = param.ga_p.max_population;
		genes = vector<gene>(n);
	}

	void active()
	{
		for (int it = 0; it < param.ga_p.max_generations; it++)
		{

			sort(genes.begin(), genes.end(), order);
			vector<gene> new_generation(n);
			
			for (int i = 0; i < param.ga_p.tx_elite; i++)
			{
				new_generation[i] = genes[i];
			}

			for (int i = param.ga_p.tx_elite; i < n; i++)
			{
				int l = utilities::random_range(0, ());
			}
		}
	}
};