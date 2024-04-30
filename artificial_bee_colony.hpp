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



};

class ABC
{
    public:
    
};