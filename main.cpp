#include "library.hpp"
#include "TSP.hpp"

int utilities::n_cities;
vector<point> utilities::city;
params utilities::param;

int main()
{
	utilities::input_points();
	utilities::param = params(PARAMS_FILE);
	TSP a;
	a.run();
}
