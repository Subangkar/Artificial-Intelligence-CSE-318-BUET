#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

#include "tspDS.h"
#include "Heuristics.h"

void printSolution(const vector<int> &TSPTourPath, CityLocation *cityLocations) {
	cout << "# of Visited Cities    : " << TSPTourPath.size() << endl;
	cout << "Total Tour Cost        : " << calculateTourCost(TSPTourPath, cityLocations) << endl;
	cout << "Visited Cities Order   : ";
	for (int i : TSPTourPath)cout << i << " ";
	cout << endl << endl;
}

//void (*heuristics_functions[])() = {NearestNeighbourHeuristic, NearestInsertionHeuristic, CheapestInsertionHeuristic,
//                                    TwoOptHeuristic, ThreeOptHeuristic};

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);

	int N;
	cin >> N;
	CityLocation cityLocations[N];

	for (int i = 0; i < N; i++)
		cin >> cityLocations[i].x >> cityLocations[i].y;

	Heuristics heuristics(cityLocations, N);

	for (int f = 0; f < 5; ++f) {
		cout << heuristics_name[f] << " :: " << endl;
//		heuristics_functions[f]();
		const tsptourpath_t &tsptour = heuristics.getTSPTourPath(heuristicFunc(f));
		printSolution(tsptour, cityLocations);
	}

}

#pragma clang diagnostic pop