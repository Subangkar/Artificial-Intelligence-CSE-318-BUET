#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

#include <chrono>
#include "Heuristics.h"
#include "tspDS.h"

void printSolution(const vector<int> &TSPTourPath, CityLocation *cityLocations) {
	cout << "# of Visited Cities    : " << TSPTourPath.size() << endl;
	cout << "Total Tour Cost        : " << calculateTourCost(TSPTourPath, cityLocations) << endl;
	cout << "Visited Cities Order   : ";
	for (int i : TSPTourPath)cout << i << " ";
	cout << endl << endl;
}

//void (*heuristics_functions[])() = {ConstructionHeuristics_NearestNeighbour, ConstructionHeuristics_NearestInsertion, ConstructionHeuristics_CheapestInsertion,
//                                    ImprovementHeuristics_2OPT, ImprovementHeuristics_3OPT};

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	srand((unsigned) time(nullptr));

	int N;
	cin >> N;
	CityLocation cityLocations[N];

	for (int i = 0; i < N; i++)
		cin >> cityLocations[i].x >> cityLocations[i].y;

	auto * heuristics = new Heuristics(cityLocations, N);

	for (int f = 0; f < 5; ++f) {
		cout << heuristics_name[f] << " :: " << endl;
//		heuristics_functions[f]();
		const tsptourpath_t &tsptour = heuristics->getTSPTourPath(heuristicFunc(f));
		printSolution(tsptour, cityLocations);
	}

	delete heuristics;
}

#pragma clang diagnostic pop