#include "library.hpp"
#include "TSP.hpp"

int utilities::n_cities;
vector<point> utilities::city;
params utilities::param(PARAMS_FILE);

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	utilities::input_points();
	TSP a;
	//a.best_params();
	a.run();
}
