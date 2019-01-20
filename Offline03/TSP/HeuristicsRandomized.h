//
// Created by Subangkar on 19-Jan-19.
//

#ifndef TSP_HEURISTICSMODIFIED_H
#define TSP_HEURISTICSMODIFIED_H

#include <set>
#include "Heuristics.h"

class HeuristicsRandomized : public Heuristics {
public:
	HeuristicsRandomized(CityLocation *cityLocations, int N) : Heuristics(cityLocations, N) {}

	virtual ~HeuristicsRandomized() {

	}

private:
	city_t findNearestUnvisited(city_t city, const vector<city_t> &skipSet) {
		double minDist = numeric_limits<double>::max();
		city_t nearestUnvisCity = EOF;
		for (city_t neighbor = 0; neighbor < N; neighbor++) {
			if (city != neighbor && !visited[neighbor] &&
			    find(skipSet.begin(), skipSet.end(), neighbor) == skipSet.end() &&
			    cityLocations[city].distanceWith(cityLocations[neighbor]) < minDist)
				minDist = cityLocations[city].distanceWith(cityLocations[neighbor]), nearestUnvisCity = neighbor;
		}
		return nearestUnvisCity;
	}

public:

//private:
	void ConstructionHeuristics_NearestNeighbour() override {
		resetBuffer();

		int k = 5;
		city_t i = getStartCity();
		tspTourPath.push_back(i);
		visited[i] = true;
		vector<city_t> skipSet;
		skipSet.reserve(k);
		while (tspTourPath.size() < N) {
			skipSet.clear();
			while (skipSet.size() < k && (tspTourPath.size() + skipSet.size()) <= N)
				skipSet.push_back(findNearestUnvisited(i, skipSet));

			city_t r = skipSet[rand() % skipSet.size()];
			tspTourPath.push_back(r);
			visited[r] = true;
			i = r;
		}
	}

	void ConstructionHeuristics_Savings() override {
		resetBuffer();

		double dist[N][N];

		for (city_t u = 0; u < N; ++u) {
			for (city_t v = 0; v < N; ++v) {
				dist[u][v] = cityLocations[u].distanceWith(cityLocations[v]);
			}
		}

		city_t d = getStartCity();

		std::priority_queue<savings_t> q;
		for (city_t u = 0, i = 0; u < N; ++u) {
			for (city_t v = u + 1; v < N; ++v, ++i) {
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
				SavingsAddEdge(adjMat, d, u);
			}
		}

		// solution generation
		int k = 5;
		vector<savings_t> bestkSavings;
		bestkSavings.reserve(k);
		size_t nMerge = 0;
		while (!q.empty() && nMerge < N - 1) {
			bestkSavings.clear();
			while (bestkSavings.size() < k && !q.empty()) {
				bestkSavings.push_back(q.top());
				q.pop();
			}

			savings_t selSave = bestkSavings[rand() % bestkSavings.size()];
			for (auto &bestkSaving : bestkSavings) {
				if (bestkSaving != selSave) {
					q.push(bestkSaving);
				}
			}
			city_t u = selSave.u, v = selSave.v;

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
};


#endif //TSP_HEURISTICSMODIFIED_H
