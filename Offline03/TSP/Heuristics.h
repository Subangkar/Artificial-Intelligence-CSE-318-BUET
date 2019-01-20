//
// Created by Subangkar on 25-Dec-18.
//

#ifndef TSP_HEURISTICS_H
#define TSP_HEURISTICS_H

#include "tspDS.h"

#define START_CITY_RANDOM ( startCity==-1 ? rand()%N : startCity) // (N-1) //

enum heuristicFunc {
	NearestNeighbor = 0, NearestInsertion, CheapestInsertion, TwoOPT, ThreeOPT, Savings, LAST
};

const char *heuristics_name[] = {"NearestNeighbour Heuristic", "NearestInsertion Heuristic",
                                 "CheapestInsertion Heuristic",
                                 "2-OPT Heuristic", "3-OPT Heuristic", "Savings Heuristic"};


double calculateTourCost(const tsptourpath_t &tourPath, CityLocation *cityLocations) {
	double costValue = 0;
	for (int i = 0; i < tourPath.size(); i++) {
		int thisCity = tourPath[i];
		int nextCity = tourPath[(i + 1) % tourPath.size()];
		costValue += cityLocations[thisCity] - cityLocations[nextCity];
	}
	return costValue;
}


class Heuristics {
protected:
	struct savings_t {
		city_t u, v;
		double savingsVal;

		bool operator<(const savings_t &rhs) const {
			return savingsVal < rhs.savingsVal;
		}

		bool operator==(const savings_t &rhs) const {
			return u == rhs.u && v == rhs.v && savingsVal == rhs.savingsVal;
		}

		bool operator!=(const savings_t &rhs) const {
			return !(*this == rhs);
		}
	};

	CityLocation *cityLocations;
	bool *visited;
	int N;
	tsptourpath_t tspTourPath;
	city_t startCity;

	void resetBuffer() {
		tspTourPath.clear();
		memset(visited, false, N * sizeof(bool));
	}


	virtual city_t findNearestUnvisited(city_t city) {
		double minDist = numeric_limits<double>::max();
		city_t nearestUnvisCity = EOF;
		for (city_t neighbor = 0; neighbor < N; neighbor++) {
			if (city != neighbor && !visited[neighbor] &&
			    cityLocations[city].distanceWith(cityLocations[neighbor]) < minDist)
				minDist = cityLocations[city].distanceWith(cityLocations[neighbor]), nearestUnvisCity = neighbor;
		}
		return nearestUnvisCity;
	}

	void insertEdgeToTourPath(city_t i, city_t r) {

		/// now path has (i-j....-r) which to be converted into (i-r-j.....)
		tspTourPath.push_back(r);

		visited[r] = true;

		// replaces edge ...i-j with ...i-r-j
		for (int k = static_cast<int>(tspTourPath.size() - 2); k >= 0 && tspTourPath[k] != i; k--) {
			swap(tspTourPath[k], tspTourPath[k + 1]);
		}
	}

	// finds the nearest unvisited one not included in current path
	city_t findOverallNearestOfAnySubTourCity() {
		double minDist = numeric_limits<double>::max();
		city_t nearestOfAll = EOF;

		/// find the minimal neighbor of any included node
		for (city_t i = 0; i < N; i++) {
			if (!visited[i]) continue; // if not included in current path ignore
			city_t r = findNearestUnvisited(i); // check nearest for this included city
			if (cityLocations[i].distanceWith(cityLocations[r]) < minDist)
				minDist = cityLocations[i].distanceWith(cityLocations[r]), nearestOfAll = r;
		}
		return nearestOfAll;
	}

	city_t findRofMinCostIncreaseInsertion(city_t &minI) {
		double minDist = numeric_limits<double>::max();
		minI = EOF;
		city_t minR = EOF;

		for (int subTourCity = 0; subTourCity < tspTourPath.size(); subTourCity++) {
			city_t i = tspTourPath[subTourCity];
			city_t j = tspTourPath[(subTourCity + 1) % tspTourPath.size()];
			for (city_t r = 0; r < N; r++) {
				if (visited[r]) continue;
				double dist =
						cityLocations[i].distanceWith(cityLocations[r]) +
						cityLocations[j].distanceWith(cityLocations[r]) -
						cityLocations[i].distanceWith(cityLocations[j]);
				if (dist < minDist) minDist = dist, minI = i, minR = r;
			}
		}
		return minR;
	}

	// replaces u-v by inserting u-w-v with min edge distance
	city_t findNearestEdge(city_t r) {
		double minDist = numeric_limits<double>::max();
		int nearestI = EOF;
		for (int edg = 0; edg < tspTourPath.size(); edg++) {
			int i = tspTourPath[edg];
			int j = tspTourPath[(edg + 1) %
			                    tspTourPath.size()]; // i-j need to be sequential becoz we've considered sequential edge only
			// cost( i-j ) > cost( i-r-j )
			double dist = (cityLocations[i].distanceWith(cityLocations[r]) +
			               cityLocations[j].distanceWith(cityLocations[r])) -
			              cityLocations[i].distanceWith(cityLocations[j]);
			// i-j edge is deleted after inserting i-r-j in sub tour that's why dist(i,j) is subtracted
			if (dist < minDist) minDist = dist, nearestI = i;
		}
		return nearestI;
	}

	// 3 bit combination for deletion & insertion of three edges
	vector<city_t> threeOPTOperation(int i, int j, int k, int mask) {
		// i..(i+1)..j..(j+1)..k => swap => i..(j+1)..k..(i+1)..j

		bool reverse2 = static_cast<bool>((mask >> 2) & 1);
		bool reverse1 = static_cast<bool>((mask >> 1) & 1);
		bool Swap = static_cast<bool>(mask & 1);

		vector<city_t> newTourPath;
		if (reverse1) reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
		if (reverse2) reverse(tspTourPath.begin() + j + 1, tspTourPath.begin() + k + 1);

		for (int x = 0; x <= i; x++) newTourPath.push_back(tspTourPath[x]);
		if (Swap) {
			for (int x = j + 1; x <= k; x++) newTourPath.push_back(tspTourPath[x]);
			for (int x = i + 1; x <= j; x++) newTourPath.push_back(tspTourPath[x]);
		} else {
			for (int x = i + 1; x <= j; x++) newTourPath.push_back(tspTourPath[x]);
			for (int x = j + 1; x <= k; x++) newTourPath.push_back(tspTourPath[x]);
		}
		for (int x = k + 1; x < N; x++) newTourPath.push_back(tspTourPath[x]);

		if (reverse1) reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
		if (reverse2) reverse(tspTourPath.begin() + j + 1, tspTourPath.begin() + k + 1);
		return newTourPath;
	}

	bool SavingsIsSameRoute(const city_t *parent, city_t u, city_t v) {
		city_t pu = parent[u], pv = parent[v];
		return pu == pv;
	}

	void SavingsMergeRoute(city_t *parent, city_t u, city_t v) {
		city_t pu = parent[u], pv = parent[v];
		city_t p = min(pu, pv);

		for (int i = 0; i < N; ++i) {
			if (parent[i] == pu || parent[i] == pv)
				parent[i] = p;
		}
	}

	void SavingsAddEdge(vector<vector<city_t >> &adjMat, city_t u, city_t v) {
		++adjMat[u][v];
		++adjMat[v][u];
	}

	void SavingsRemoveEdge(vector<vector<city_t >> &adjMat, city_t u, city_t v) {
		--adjMat[u][v];
		--adjMat[v][u];
	}

public:
	Heuristics(CityLocation *cityLocations, int N) : N(N) {
		this->cityLocations = cityLocations;
		visited = new bool[N];
		startCity = -1;
		tspTourPath.reserve(N);
	}

	void setStartCity(city_t startCity);

	city_t getStartCity();

	virtual void ConstructionHeuristics_NearestNeighbour() {
		resetBuffer();

		city_t i = getStartCity();
		tspTourPath.push_back(i);
		visited[i] = true;

		while (tspTourPath.size() < N) {
			city_t r = findNearestUnvisited(i);
			tspTourPath.push_back(r);
			visited[r] = true;
			i = r;
		}
	}

	void ConstructionHeuristics_NearestInsertion() {
		resetBuffer();

		city_t i = getStartCity();
		tspTourPath.push_back(i);
		visited[i] = true;
		city_t r = findNearestUnvisited(i);
		tspTourPath.push_back(r);
		visited[r] = true;

		while (tspTourPath.size() < N) {
			r = findOverallNearestOfAnySubTourCity();
			i = findNearestEdge(r);
			insertEdgeToTourPath(i, r);
		}
	}

	void ConstructionHeuristics_CheapestInsertion() {
		resetBuffer();

		city_t i = getStartCity();
		tspTourPath.push_back(i);
		visited[i] = true;

		city_t r = findNearestUnvisited(i);
		tspTourPath.push_back(r);
		visited[r] = true;

		while (tspTourPath.size() < N) {
			r = findRofMinCostIncreaseInsertion(i);
			insertEdgeToTourPath(i, r);
		}
	}

	virtual void ConstructionHeuristics_Savings();

	void ImprovementHeuristics_2OPT() {
		resetBuffer();

		// start with an arbitary soln
		ConstructionHeuristics_NearestNeighbour();

		while (true) {
			double currentCost = calculateTourCost(tspTourPath, cityLocations);
			bool isChanged = false;

			// deletes 2 edges between i,j   i-/-(i+1)-/-...-/-j--x => reverse (i+1) to (j) => i---j--...--(i+1)---x
			for (int i = 0; i < tspTourPath.size(); i++) {
				for (int j = i + 2; j < tspTourPath.size(); j++) {
					reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
					double newCost = calculateTourCost(tspTourPath, cityLocations);
					if (newCost < currentCost) {
						isChanged = true;
						break;
					}
					reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
				}
				if (isChanged) break;
			}
			if (!isChanged) break;
		}
	}

	void ImprovementHeuristics_3OPT() {
		resetBuffer();

		ConstructionHeuristics_NearestNeighbour();
		while (true) {
			double currentCost = calculateTourCost(tspTourPath, cityLocations);
			bool isChanged = false;

			for (int i = 0; i < tspTourPath.size(); i++) {
				for (int j = i + 2; j < tspTourPath.size(); j++) {
					for (int k = j + 2; k < tspTourPath.size(); k++) {
						for (int mask = 1; mask < 8; mask++) {
							vector<city_t> newTour = threeOPTOperation(i, j, k, mask);
							double newCost = calculateTourCost(newTour, cityLocations);
							if (newCost < currentCost) {
								isChanged = true;
								tspTourPath = newTour;
								break;
							}
						}
						if (isChanged) break;
					}
					if (isChanged) break;
				}
			}
			if (!isChanged) break;
		}
	}

	const tsptourpath_t &getTSPTourPath(heuristicFunc funcType) {

		switch (funcType) {
			case NearestNeighbor:
				ConstructionHeuristics_NearestNeighbour();
				break;
			case NearestInsertion:
				ConstructionHeuristics_NearestInsertion();
				break;
			case CheapestInsertion:
				ConstructionHeuristics_CheapestInsertion();
				break;
			case TwoOPT:
				ImprovementHeuristics_2OPT();
				break;
			case ThreeOPT:
				ImprovementHeuristics_3OPT();
				break;
			case Savings:
				ConstructionHeuristics_Savings();
				break;
		}

		return tspTourPath;
	}

	virtual ~Heuristics() {
		delete[] visited;
		visited = nullptr;
	}
};

void Heuristics::ConstructionHeuristics_Savings() {
	resetBuffer();

	double dist[N][N];

	for (city_t u = 0; u < N; ++u) {
		for (city_t v = 0; v < N; ++v) {
			dist[u][v] = cityLocations[u].distanceWith(cityLocations[v]);
		}
	}

	city_t d = getStartCity();

	std::priority_queue<savings_t> q;
	for (city_t u = 0; u < N; ++u) {
		for (city_t v = u + 1; v < N; ++v) {
			if (u != d && v != d)
				q.push({u, v, (dist[u][d] + dist[d][v] - dist[u][v])});
		}
	}

	vector<vector<city_t>> adjMat(N, vector<city_t>(N, 0));// init to 0
	city_t parent[N];
	for (city_t u = 0; u < N; ++u) {
		parent[u] = u;
	}

	for (city_t u = 0; u < N; ++u) {
		if (u != d) {
			SavingsAddEdge(adjMat, u, d);
			SavingsAddEdge(adjMat, u, d);
		}
	}

	// solution generation
	size_t nMerge = 0;
	while (!q.empty() && nMerge < N - 1) {
		city_t u = q.top().u, v = q.top().v;
		q.pop();

		if (!SavingsIsSameRoute(parent, u, v) && adjMat[u][d] && adjMat[d][v]) {
			// not in the same route and has direct edge to depot then merge

			SavingsAddEdge(adjMat, u, v);
			SavingsMergeRoute(parent, u, v);
			SavingsRemoveEdge(adjMat, u, d);
			SavingsRemoveEdge(adjMat, v, d);

			++nMerge;
		}

	}

	// solution construction
	city_t s = d;
	do {
		for (int i = 0; i < N; ++i) {
			if (adjMat[s][i] == 1) {
				tspTourPath.push_back(s);
				SavingsRemoveEdge(adjMat, s, i);// removes the edge so that same edge doesn't come twice
				s = i;
			}
		}
	} while (s != d);

}

void Heuristics::setStartCity(city_t startCity) {
	Heuristics::startCity = startCity;
}

city_t Heuristics::getStartCity() {
	startCity = START_CITY_RANDOM;
	return startCity;
}


#endif //TSP_HEURISTICS_H
