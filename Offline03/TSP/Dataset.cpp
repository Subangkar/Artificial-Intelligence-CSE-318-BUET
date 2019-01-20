//
// Created by Subangkar on 19-Jan-19.
//

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


tsptourpath_t
getResultStat(int &N, Heuristics &heuristics, heuristicFunc f, double &best, double &avg,
              double &worst, size_t k) {
	best = numeric_limits<double_t>::max(), worst = 0, avg = 0;
	tsptourpath_t bestTour;
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
			bestTour = tsptour;
		}
		if (curCost > worst) {
			worst = curCost;
		}
		avg += (curCost / k);
//		printSolution(tsptour, cityLocations);
		N = static_cast<int>(tsptour.size());
	}
	return bestTour;
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


tsptourpath_t getResultStat2OPT(int &N, HeuristicsRandomized &heuristics, bool first, double &best, double &avg,
                                double &worst, vector<tsptourpath_t> tours) {
	best = numeric_limits<double_t>::max(), worst = 0, avg = 0;
	tsptourpath_t bestTour;
	for (const auto &tour:tours) {
		const tsptourpath_t &tsptour = first ? heuristics.ImprovementHeuristics_2OPT_First(tour) :
		                               heuristics.ImprovementHeuristics_2OPT_Best(tour);
		double curCost = calculateTourCost(tsptour, cityLocations);
		if (curCost < best) {
			best = curCost;
			bestTour = tsptour;
		}
		if (curCost > worst) {
			worst = curCost;
		}
		avg += (curCost / tours.size());
//		printSolution(tsptour, cityLocations);
		N = static_cast<int>(tsptour.size());
	}
	return bestTour;
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
	auto k = static_cast<size_t>(N);


	int cityNo;
	for (int i = 0; i < N; i++)
		if (argc != 3) cin >> cityLocations[i].x >> cityLocations[i].y;
		else cin >> cityNo >> cityLocations[i].x >> cityLocations[i].y;

	cout << argv[1] << " :: " << endl;

//========================== Best Starting Location from Greedy Simple =========================
	city_t bestStartCity[LAST];
	tsptourpath_t bestSimpleTour;
	{
		cout << endl << "Greedy Simple :: " << endl;
		auto *heuristics = new Heuristics(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = static_cast<size_t>(N);
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			bestSimpleTour = getResultStat(n, *heuristics, heuristicFunc(f), best, avg, worst, k);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n,
			       bestSimpleTour.front(),
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());
			bestStartCity[f] = bestSimpleTour.front();
		}

		delete heuristics;
	}
//==============================================================================================


//========================== 3-Best Tours From Random Greedy ===================================
	vector<tsptourpath_t> bestTours[LAST]; // for Savings,NNH
	{
		cout << endl << "Greedy Randomized :: " << endl;
		auto *heuristics = new HeuristicsRandomized(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = static_cast<size_t>(N);
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			bestTours[f] = getResultStatRandom(n, *heuristics, heuristicFunc(f), best, avg, worst,
			                                   bestStartCity[f], 10);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n,
			       bestTours[f][1][0],
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());
			bestTours[f].insert(bestTours[f].begin(), bestSimpleTour);
		}

//		delete heuristics;
	}
//==============================================================================================
// 1-> Simple.Best 2-> Random->Best.1 3-> Random->Best.2 4-> Random->Best.3


//================================= 2-OPT First IMP ============================================
	double best_first_NNH, best_first_SH;
	{
		cout << endl << "2OPT First :: " << endl;
		auto *heuristics = new HeuristicsRandomized(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = static_cast<size_t>(N);
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			tsptourpath_t bestTour = getResultStat2OPT(n, *heuristics, true, best, avg, worst, bestTours[f]);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n,
			       bestTour[0],
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());

			if (f == NearestNeighbor)best_first_NNH = best;
			if (f == Savings)best_first_SH = best;
		}

//		delete heuristics;
	}
//==============================================================================================


//================================= 2-OPT Best IMP =============================================
	double best_best_NNH, best_best_SH;
	{
		cout << endl << "2OPT Best  :: " << endl;
		auto *heuristics = new HeuristicsRandomized(cityLocations, N);
		double best = 0, worst = 0, avg = 0;
		int heu[] = {NearestNeighbor, Savings};
		printf("%30s - %3s - %10s - %10s - %10s - %10s  -  %10s\n", "HeuristicName", "###", "Best Start",
		       "Best case",
		       "Worst case", "Avg case", "Exec time");
		k = static_cast<size_t>(N);
		for (int f : heu) {
			auto startTime = chrono::steady_clock::now();
			int n = N;
			tsptourpath_t bestTour = getResultStat2OPT(n, *heuristics, false, best, avg, worst, bestTours[f]);
			auto endTime = chrono::steady_clock::now();
			auto diff = endTime - startTime;
			printf("%30s - %3d - %10d - %10.2f - %10.2f - %10.2f  -  %7.2f ms\n", heuristics_name[f], n,
			       bestTour[0],
			       best,
			       worst, avg, chrono::duration<double, milli>(diff).count());

			if (f == NearestNeighbor)best_best_NNH = best;
			if (f == Savings)best_best_SH = best;
		}

//		delete heuristics;
	}
//==============================================================================================

//========================================= Ratio Print ========================================
	{
		printf("%30s - %30s\n", "Best Improvement", "First Improvement");
		printf("%14s  %14s - %14s  %14s\n", "NNH", "SH", "NNH", "SH");
		printf("%14.2f  %14.2f - %14.2f  %14.2f\n", best_best_NNH, best_best_SH, best_first_NNH, best_first_SH);
	}
	FILE *fp = fopen("out.txt", "w");
	fprintf(fp, "%14.2f  %14.2f \n%14.2f  %14.2f\n", best_best_NNH, best_best_SH, best_first_NNH, best_first_SH);
//==============================================================================================
}


