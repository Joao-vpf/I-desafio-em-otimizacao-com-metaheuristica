#pragma once
#include "library.hpp"

class annealing
{
public:
    /*
        Objective:
            Main class responsible for executing the annealing algorithm.

        Attributes:
            t0 - Initial temperature.
            tf - Final temperature.
            l - Number of iterations (exchanges) to be performed on the current solution.
            alfa - Temperature variation rate.
            s - Vector containing the best path.
            s_cost - Cost of the current solution.
    */

    LD t0;
    LD tf;
    int l;
    LD alfa;
    vector<int> s;
    LD s_cost;

    annealing(vector<int> s_initial, LD s_cost_initial)
    {
        t0 = utilities::param.ann_p.t0;
        tf = utilities::param.ann_p.tf;
        l = utilities::param.ann_p.l;
        alfa = utilities::param.ann_p.alfa;
        s = s_initial;
        s_cost = s_cost_initial;
    }

    LD solution()
    {
        LD t = t0;
        for(int i = 0; i < l && t>=tf; i++)
        {
            vector<int> n_s = s;

            random_shuffle(n_s.begin(),n_s.end());
            LD ns_cost = utilities::Fx_fit(n_s,utilities::n_cities);
            LD delta = ns_cost - s_cost;
            
            if (delta < 0 || exp(-delta / t) > ((LD)rand() / RAND_MAX))
            {
                s_cost = ns_cost;
                s = n_s;
            }

            if(s_cost == ns_cost)
                s = n_s;

            t = alfa*t;
        }

        return s_cost; 
    }

};
