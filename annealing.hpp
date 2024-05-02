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
            alpha - Temperature variation rate.
            best_solution - Vector containing the best path.
            s_cost - Cost of the current best_solution.
    */

    LD t0;
    LD tf;
    int l;
    LD alpha;
    vector<int> best_solution;
    LD s_cost;

    annealing(vector<int> s_initial, LD s_cost_initial)
    {
        t0 = utilities::param.ann_p.t0;
        tf = utilities::param.ann_p.tf;
        l = utilities::param.ann_p.l;
        alpha = utilities::param.ann_p.alpha;
        best_solution = s_initial;
        s_cost = s_cost_initial;
    }

    void perturbPath(std::vector<int> &path)
    {
        int idx1 = utilities::random_range(0, path.size() - 1);
        int idx2 = utilities::random_range(0, path.size() - 1);
        std::swap(path[idx1], path[idx2]);
    }

    LD solution()
    {
        LD t = t0;
        vector<int> local_s = best_solution;
        LD local_cost = s_cost;

        while (t >= tf)
        {
            for (int i = 0; i < l; i++)
            {
                vector<int> n_s = local_s;

                perturbPath(n_s);

                LD ns_cost = utilities::Fx_fit(n_s, utilities::n_cities);
                LD delta = ns_cost - local_cost;

                if (delta < 0 || exp(-delta / t) > ((LD)rand() / RAND_MAX))
                {
                    local_cost = ns_cost;
                    local_s = n_s;
                }

                if (local_cost <= s_cost)
                {
                    best_solution = local_s;
                    s_cost = local_cost;
                }

                t = t * alpha;
            }
        }

        return s_cost;
    }
};
