#pragma once
#include "library.hpp"

class ABC
{   
    int n_city;
    int cycles_limit;
    int colony_size;
    double scout_percent;
    double onlooker_percent;
    double employed_percent;
    vector<int> best_solution;
    LD solution_cost;


public:
    ABC(vector<int> initial_solution,LD initial_cost){

        n_city = utilities::n_cities;
        cycles_limit = utilities::param.abc_p.cycles_limit;
        colony_size = utilities::param.abc_p.colony_size;
        scout_percent = utilities::param.abc_p.onlooker_percent;
        onlooker_percent = utilities::param.abc_p.onlooker_percent;
        employed_percent = utilities::param.abc_p.employed_percent;
        best_solution = initial_solution;
        solution_cost = initial_cost;

    }

    void scouter_bee(){

    }

    LD solution(){
        
    }
};