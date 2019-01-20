//
// Created by Subangkar on 19-Jan-19.
//
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc30-c"

#include <chrono>
#include <set>
#include <map>
#include "Heuristics.h"
#include "HeuristicsRandomized.h"
#include "tspDS.h"


CityLocation cityLocations[10000];


void printSolution(const vector<int> &TSPTourPath, CityLocation *cityLocations) {
	cout << "# of Visited Cities    : " << TSPTourPath.size() << endl;
	cout << "Total Tour Cost        : " << calculateTourCost(TSPTourPath, cityLocations) << endl;
	cout << "Visited Cities Order   : ";
//	for (int i : TSPTourPath)cout << i << " ";
	cout << endl << endl;
}

//void (*heuristics_functions[])() = {ConstructionHeuristics_NearestNeighbour, ConstructionHeuristics_NearestInsertion, ConstructionHeuristics_CheapestInsertion,
//                                    ImprovementHeuristics_2OPT, ImprovementHeuristics_3OPT};


city_t
getResultStat(CityLocation cityLocations[], int &N, Heuristics &heuristics, heuristicFunc f, double &best, double &avg,
              double &worst, size_t k) {
	best = numeric_limits<double_t>::max(), worst = 0, avg = 0;
	city_t bestStart = -1;
	set<city_t> startCities;
	city_t startCity;
	for (size_t i = 0; i < k; ++i) {
		do
			startCity = rand() % N;
		while (startCities.find(startCity) != startCities.end());
		startCities.insert(startCity);
		heuristics.setStartCity(startCity);
		const tsptourpath_t &tsptour = heuristics.getTSPTourPath(heuristicFunc(f));
		double curCost = calculateTourCost(tsptour, cityLocations);
		if (curCost < best) {
			best = curCost;
			bestStart = tsptour[0];
		}
		if (curCost > worst) {
			worst = curCost;
		}
		avg += (curCost / k);
//		printSolution(tsptour, cityLocations);
		N = static_cast<int>(tsptour.size());
	}
	return bestStart;
}

vector<tsptourpath_t>
getResultStatRandom(int &N, Heuristics &heuristics, heuristicFunc f, double &best, double &avg,
                    double &worst, city_t startCity, size_t n) {
	struct Compare {
		bool operator()(const tsptourpath_t &lhs, const tsptourpath_t &rhs) {
			return calculateTourCost(lhs, cityLocations) > calculateTourCost(rhs, cityLocations);
		}
	};


	best = numeric_limits<double_t>::max(), worst = 0, avg = 0;
	vector<tsptourpath_t> bestTours;
	std::priority_queue<tsptourpath_t, std::vector<tsptourpath_t>, Compare> pq;
	set<city_t> startCities;
	for (size_t i = 0; i < n; ++i) {
		startCities.insert(startCity);
		heuristics.setStartCity(startCity);
		const tsptourpath_t &tsptour = heuristics.getTSPTourPath(heuristicFunc(f));
		double curCost = calculateTourCost(tsptour, cityLocations);
		if (curCost < best) {
			best = curCost;
		}
		if (curCost > worst) {
			worst = curCost;
		}
		avg += (curCost / n);
//		printSolution(tsptour, cityLocations);
		N = static_cast<int>(tsptour.size());
		pq.push(tsptour);
	}

	for (int i = 0; i < 3; ++i) {
		bestTours.push_back(pq.top());
		pq.pop();
	}
	return bestTours;
}

int main(int argc, const char *argv[]) {
	if (argc > 1) {
		freopen(argv[1], "r", stdin);
	} else
		freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);

	srand((unsigned) time(nullptr));

	int N;
	cin >> N;
	size_t k = N;


	int cityNo;
	for (int i = 0; i < N; i++)
		if (argc != 3) cin >> cityLocations[i].x >> cityLocations[i].y;
		else cin >> cityNo >> cityLocations[i].x >> cityLocations[i].y;

	cout << argv[1] << " :: " << endl;
	city_t bestStartCity[10];
	{
		cout << endl << "Greedy Simple :: " << endl;
		auto *heuristics = new Heuristics(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = N;
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			city_t bestStart = getResultStat(cityLocations, n, *heuristics, heuristicFunc(f), best, avg, worst, k);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n, bestStart,
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());
			bestStartCity[f] = bestStart;
		}

		delete heuristics;
	}


	{
		cout << endl << "Greedy Randomized :: " << endl;
		auto *heuristics = new HeuristicsRandomized(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = N;
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			vector<tsptourpath_t> bestTours = getResultStatRandom(n, *heuristics, heuristicFunc(f), best, avg, worst,
			                                                      bestStartCity[f], k);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n,
			       bestTours[1][0],
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());

		}

//		delete heuristics;
	}


}

#pragma clang diagnostic pop

