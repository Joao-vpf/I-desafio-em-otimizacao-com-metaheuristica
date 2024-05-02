#pragma once
#include "library.hpp"

class grasp
{
public:
    int l;
    int m;
    vector<int> cont_alpha;
    vector<double> p_alpha;
    vector<double> solution_alpha;
    vector<double> alpha;
    int beta;
    vector<int> best_solution;
    LD best_cost;

    grasp(vector<int> s_initial, LD s_cost_initial)
    {
        best_solution = s_initial;
        best_cost = s_cost_initial;
        m = utilities::param.grasp_p.m;
        p_alpha = vector<double>(m, 1 / m);
        cont_alpha = vector<int>(m, 0);
        solution_alpha = vector<double>(m, 1 / m);
        alpha = utilities::param.grasp_p.alpha;
        beta = utilities::param.grasp_p.beta;
        l = utilities::param.grasp_p.l;
    }

    vector<int> greedyRandomizedConstruction(double alpha)
    {
        vector<int> solution;
        vector<point> candidate_list = utilities::city;
        vector<int> candidate_Position;
        vector<LD> candidate_dist;

        for (int i = 0; i < utilities::n_cities; i++)
            candidate_Position.push_back(i);

        int index = utilities::random_range(0, candidate_list.size());
        solution.push_back(candidate_Position[index]);

        candidate_Position.erase(candidate_Position.begin() + index);
        candidate_list.erase(candidate_list.begin() + index);


        while (!candidate_list.empty())
        {

            double d_min = numeric_limits<double>::infinity();
            double d_max = -1.0;
            for (int k = 0; k < candidate_list.size(); k++)
            {
                double d = utilities::euclidian_distance(utilities::city[solution.back()], candidate_list[k]);
                candidate_dist.push_back(d);
                d_min = min(d_min, d);
                d_max = max(d_max, d);
            }

            vector<pair<int,int>> RCL;

            for (int i = 0; i < candidate_dist.size(); i++)
            {
                if (candidate_dist[i] <= d_min + alpha * (d_max - d_min))
                {   
                    RCL.push_back(make_pair(candidate_Position[i],i));
                }
            }

            int randomIndex = utilities::random_range(0, RCL.size());
            solution.push_back(RCL[randomIndex].first);
            
            candidate_dist.clear();

            candidate_Position.erase(candidate_Position.begin() + RCL[randomIndex].second);
            candidate_list.erase(candidate_list.begin() + RCL[randomIndex].second);
        }

        return solution;
    }

    void local_Search(vector<int> solution_local)
    {
        int n_cities = utilities::n_cities;
        bool improved = true;
        double local_Cost = utilities::Fx_fit(solution_local, n_cities);

        while (improved)
        {
            improved = false;

            for (int i = 1; i < n_cities - 1; ++i)
            {
                for (int j = i + 1; j < n_cities; ++j)
                {
                    swap(solution_local[i], solution_local[j]);
                    double newCost = utilities::Fx_fit(solution_local, n_cities);

                    if (newCost < local_Cost)
                    {
                        local_Cost = newCost;
                        improved = true;
                    }
                    else
                    {
                        swap(solution_local[i], solution_local[j]);
                    }
                }
            }
        }
        if (best_cost > local_Cost)
        {
            best_solution = solution_local;
            best_cost = local_Cost;
        }
    }

    void update_probability(int i)
    {
        if (i % beta == 0)
        {
            vector<double> a(m);
            vector<double> q(m);
            vector<double> p(m);

            for (int i = 0; i < m; ++i)
            {
                if (solution_alpha[i])
                    a[i] = solution_alpha[i] / cont_alpha[i];
                else
                    a[i] = best_cost;
            }

            double sum_q = 0.0;
            for (int i = 0; i < m; ++i)
            {
                q[i] = INF - best_cost / a[i];
                sum_q += q[i];
            }

            for (int i = 0; i < m; ++i)
            {
                p[i] = q[i] / sum_q;
            }
        }
    }

    int select_alpha()
    {

        double sum_p = 0.0;
        double rng = utilities::random_range(0, 1);

        for (int i = 0; i < m; i++)
        {
            sum_p += p_alpha[i];
            if (rng <= sum_p)
            {
                return i;
            }
        }

        return m - 1;
    }

    LD solution()
    {

        for (int i = 0; i < l; i++)
        {
            int index = select_alpha();

            cont_alpha[index]++;
            vector<int> solution = greedyRandomizedConstruction(alpha[index]);
            
            local_Search(solution);
            cout << endl
                 << i << ": " << best_cost << endl;

            solution_alpha[index] += best_cost;

            update_probability(i);
        }

        return best_cost;
    }
};