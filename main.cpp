#include "library.hpp"
#include "TSP.hpp"

int utilities::n_cities;
LD utilities::input_predicted;
vector<point> utilities::city;
params utilities::param(PARAMS_FILE);

int main()
{
	utilities::input_points();
	TSP a;
	a.run();
}
