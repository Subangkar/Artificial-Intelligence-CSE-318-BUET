//
// Created by Subangkar on 19-Jan-19.
//

#ifndef TSP_HEURISTICSMODIFIED_H
#define TSP_HEURISTICSMODIFIED_H

#include <set>
#include "Heuristics.h"

class HeuristicsModified : public Heuristics {
public:
	HeuristicsModified(CityLocation *cityLocations, int N) : Heuristics(cityLocations, N) {}

	virtual ~HeuristicsModified() {

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
		city_t i = START_CITY_RANDOM;
		tspTourPath.push_back(i);
		visited[i] = true;
		vector<city_t> skipSet;
		skipSet.reserve(k);
		while (tspTourPath.size() < N) {
			skipSet.clear();
			while (skipSet.size() < k)
				skipSet.push_back(findNearestUnvisited(i, skipSet));

			city_t r = skipSet[rand() % k];
			tspTourPath.push_back(r);
			visited[r] = true;
			i = r;
		}
	}

	void ConstructionHeuristics_Savings() override {
	}
};


#endif //TSP_HEURISTICSMODIFIED_H
