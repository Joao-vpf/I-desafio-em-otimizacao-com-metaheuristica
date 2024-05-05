#pragma once
#include "library.hpp"

class ACO
{
    /*
        Objective:
            Class for implementing Ant Colony Optimization (ACO) algorithm for solving the Traveling Salesman Problem (TSP).
            This class provides methods for initializing maps, performing ant colony simulation, and obtaining the best path and fitness value.

        Attributes:
            best_path: The best path found by the ACO algorithm.
            attr: Map storing the attractiveness between cities.
            trail_phero: Map storing the pheromone trail between cities.
            nodes: Number of cities.
            best_fit: The fitness value of the best path found.
    */

    vector<int> best_path;
    unormap<pair<int,int>, LD, hash_pair> attr, trail_phero;
    int nodes;
    LD best_fit;
    
    void local_search_2_opt()
    {
        /*
            Objective:
                Perform local search using 2-opt optimization technique to improve the current path.
                This method iteratively applies the 2-opt heuristic for a specified number of iterations.

        */

        for (int it = 1; it <= utilities::param.aco_p.max_opt_it; it++)
            utilities::opt_2(best_path, best_fit);
    }

    int city_selection(const vector<vector<LD>>& prob, const set<int>& contain)
    {
        /*
            Objective:
                Select a city based on probability for the ant's movement.

            Parameters:
                - prob: Probability matrix indicating the likelihood of selecting each city.
                - contain: Set of cities already visited by the ant.

            Returns:
                The index of the selected city.
        */

        LD cut = utilities::random_range_double(0, 1);

        for (int i = 0; i < nodes; i++)
            if (cut <= prob[i][2] && !contain.count(i))
                return i;

        return -1;
    }

    vector<vector<LD>> city_probability(const int& city, const set<int>& contain)
    {
        /*
            Objective:
                Calculate the probability of selecting each city based on attractiveness and pheromone trails.

            Parameters:
                - city: Index of the current city.
                - contain: Set of cities already visited by the ant.

            Returns:
                Probability matrix indicating the likelihood of selecting each city.
        */

        LD sum = 0;
        vector<vector<LD>> probability(nodes, vector<LD>(3, 0));

        for (int i = 0; i < nodes; i++)
            if (!contain.count(i))
                probability[i][0] = pow(attr[{i, city}], utilities::param.aco_p.alpha) * pow(attr[{i, city}], utilities::param.aco_p.beta);

        for (int i = 0; i < nodes; i++)
            sum += probability[i][0];

        for (int i = 0; i < nodes; i++)
        {
            if (!contain.count(i) && sum != 0)
                probability[i][1] = probability[i][0] / sum;

            if (i == 0)
                probability[i][2] = probability[i][1]; 
            else
                probability[i][2] = probability[i][1] + probability[i - 1][2];
        }

        for (auto e : contain)
            probability[e][2] = 0;   
                      
        return probability;
    }
    
    void update_trail()
    {
        /*
            Objective:
                Update the pheromone trail after each iteration of ant movement.
        */
        for (int i = 0; i < nodes; i++) 
            trail_phero[{best_path[i], best_path[i + 1]}]++;
    }

    void ants_for_sugar()
    {
        /*
            Objective:
                Simulate ant movement to find an optimal path for the TSP.
        */

        vector<int> city_list(nodes);
        for (int i = 0; i < utilities::param.aco_p.ants; i++)
        {
            set<int> contain;
            city_list[0] = (utilities::param.aco_p.fix_init == -1 ? utilities::random_range(0, nodes) : utilities::param.aco_p.fix_init);
            contain.insert(city_list[0]);

            for (int j = 1; j < nodes; j++)
            {
                vector<vector<LD>> probability = city_probability(j, contain);
                int path_point = city_selection(probability, contain);
                
                if (path_point == -1)
                    for (int l = 0; l < nodes && path_point == -1; l++)
                        if (!contain.count(l))
                            path_point = l;

                city_list[j] = path_point;
                contain.insert(path_point);
            }
            
            LD new_fit = utilities::Fx_fit(city_list, nodes);
            if (new_fit < best_fit)
                best_path = city_list, best_fit = new_fit;
        }
        
        if (utilities::param.aco_p.local_search)
            local_search_2_opt();

        update_trail();
    }

    void simulation()
    {
        /*
            Objective:
                Perform the ACO simulation to find an optimal solution for the TSP.
        */

        int it = 1;

        while (it < utilities::param.aco_p.max_generations)
        {
            if (utilities::param.aco_p.verbose)
                print_verbose(it);  

            ants_for_sugar();
            
            for (auto& e : trail_phero)
                e.second -= utilities::param.aco_p.decay;

            it++;
        }
    }

    void print_verbose(const int& x)
    {
        /*
            Objective:
                Print verbose information including the best fitness value and the current path.
        */

        cout << "ACO Generation " << x << ":\n";
        cout << "Best: " << best_fit << " cust\n";
        
        if (utilities::param.ga_p.simple_verbose == 0)
        {
            cout << "Path: ";
            for (int i = 0; i < nodes; i++)
            {
                cout << best_path[i];
                if (i + 1 < nodes)
                {
                    cout << " ";
                }
            }
            cout << endl;
        }
    }

    void initializer_maps()
    {
        /*
            Objective:
                Initialize the attractiveness and pheromone trail maps.
        */

        for (int i = 0; i < nodes; i++)
        {
            for (int j = i; j < nodes; j++)
            {
                LD dist = utilities::euclidian_distance(utilities::city[i], utilities::city[j]);
                if (i == j || dist == 0)
                    attr[{i, j}] = attr[{j, i}] = 0.000001, trail_phero[{i, j}] = trail_phero[{j, i}] = 1.0;
                else
                    attr[{i, j}] = attr[{j, i}] = 1.0 / dist, trail_phero[{i, j}] = trail_phero[{j, i}] = 1.0;
            }
        }
    }

    void init()
    {
        /*
            Objective:
                Initialize the ACO algorithm by setting up maps and data structures.
        */
        
        initializer_maps();
    }
    
public:

    ACO()
    {
        /*
            Objective:
                Constructor for initializing the ACO algorithm.
        */

        nodes = utilities::n_cities;
        vector<bool> contain(nodes, 0);
        best_path.assign(nodes, -1);
        utilities::random_path((utilities::param.aco_p.fix_init == -1 ? utilities::random_range(0, nodes) : utilities::param.aco_p.fix_init), 0, best_fit, best_path, contain);
    }
    
    ACO(vector<int> path)
    {
        /*
            Objective:
                Constructor for initializing the ACO algorithm with a specified initial path.

            Parameters:
                - path: Initial path for the ACO algorithm.
        */

        nodes = utilities::n_cities;
        best_path = path;
        best_fit = utilities::Fx_fit(path, nodes);
    }

    void active()
    {
        /*
            Objective:
                Activate the ACO algorithm to find the optimal solution for the TSP.
        */

        init();
        simulation();
    } 

    vector<int> get_best_path()
    {
        /*
            Objective:
                Get the best path found by the ACO algorithm.

            Returns:
                The best path as a vector of city indices.
        */
        return best_path;
    }

    LD get_best_fit()
    {
        /*
            Objective:
                Get the fitness value of the best path found by the ACO algorithm.

            Returns:
                The fitness value of the best path.
        */
        return best_fit;
    }
};  