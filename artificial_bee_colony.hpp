#pragma once
#include "library.hpp"
#include "genetic.hpp"

class bee
{
    public:
    LD fit;
    int nodes;
    vector<int> path, repath;
    vector<bool> contain;

    bee(int n)
	{
		/*
			Objective:
				bee class constructor.
		*/

		nodes = n;
		path.assign(n, -1);
		repath.assign(n, -1);
		contain.assign(n, 0);
	}

    void copy(gene a)
    {
		/*
			Objective:
                Method that copies the gene class and inserts it into the bee class.
		*/

        this->fit = a.fit;
        this->path = a.path;
        this->nodes = a.nodes;
        this->repath = a.repath;
        this->contain = a.contain;
    }

    void random_path(const int& initial, bool reapeat = 0)
	{
		/*
			Objective:
				Method that creates a random path.
		*/

		path[0] = initial;
		repath[initial] = 0;
		contain[initial] = 1;
		
		for (int i = 1; i < nodes; i++)
		{
			int idx = utilities::random_range(0, nodes);
			
			while (!reapeat && contain[idx])
			{
				idx = utilities::random_range(0, nodes);
			}

			path[i] = idx;
			repath[idx] = i;
			contain[idx] = 1;
		}
		this->fit = utilities::Fx_fit(this->path, this->nodes, this->contain);
	}

};

class ABC
{
    public:
    
};