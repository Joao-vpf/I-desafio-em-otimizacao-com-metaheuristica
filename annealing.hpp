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

    annealing(annealing_params param,vector<int> s_initial, LD s_cost_initial)
    {
        t0 = param.t0;
        tf = param.tf;
        l = param.l;
        alfa = param.alfa;
        s = s_initial;
        s_cost = s_cost_initial;
    }

    void solution(){
        LD t = t0;
        for(int i = 0;i<l;i++){
            vector<int> n_s = s;

            random_shuffle(n_s.begin(),n_s.end());
            LD ns_cost = utilities::Fx_fit(n_s,n_s.size());
            LD delta = ns_cost - s_cost;

            if(delta<0){
                s_cost = ns_cost;
            }else if(exp(-delta / t) > ((double) rand() / RAND_MAX)) {
                s_cost = ns_cost;
            }

            if(s_cost = ns_cost){
                s = n_s;
            }
            t = alfa*t;

        }
    }

};
