//
// Created by Subangkar on 25-Dec-18.
//

#ifndef TSP_HEURISTICS_H
#define TSP_HEURISTICS_H

#include "tspDS.h"

enum heuristicFunc {
	NearestNeighbor = 0, NearestInsertion, CheapestInsertion, TwoOPT, ThreeOPT
};

const char *heuristics_name[] = {"NearestNeighbour Heuristic", "NearestInsertion Heuristic",
                                 "CheapestInsertion Heuristic",
                                 "2-OPT Heuristic", "3-OPT Heuristic"};


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
	CityLocation *cityLocations;
	bool *visited;
	int N;
	tsptourpath_t tspTourPath;

	void resetBuffer() {
		tspTourPath.clear();
		memset(visited, false, N * sizeof(bool));
	}


	city_t findNearestUnvisited(city_t city) {
		double minDist = numeric_limits<double>::max();
		city_t neighbor = EOF;
		for (city_t i = 0; i < N; i++) {
			if (!visited[i] && cityLocations[city].distanceWith(cityLocations[i]) < minDist)
				minDist = cityLocations[city].distanceWith(cityLocations[i]), neighbor = i;
		}
		return neighbor;
	}

	city_t findNearestOverall() {
		double minDist = numeric_limits<double>::max();
		city_t neighbor = EOF;
		for (city_t i = 0; i < N; i++) {
			if (!visited[i]) continue;
			city_t nearest = findNearestUnvisited(i);
			if (cityLocations[i].distanceWith(cityLocations[nearest]) < minDist)
				minDist = cityLocations[i].distanceWith(cityLocations[nearest]), neighbor = nearest;
		}
		return neighbor;
	}

	int findNearestEdge(int node) {
		double Min = numeric_limits<double>::max();
		int Idx = -1;
		for (int edge = 0; edge < tspTourPath.size(); edge++) {
			int x = tspTourPath[edge];
			int y = tspTourPath[(edge + 1) % tspTourPath.size()];
			double Dist = cityLocations[x].distanceWith(cityLocations[node]) +
			              cityLocations[y].distanceWith(cityLocations[node]) -
			              cityLocations[x].distanceWith(cityLocations[y]);
			if (Dist < Min) Min = Dist, Idx = x;
		}
		return Idx;
	}

	vector<city_t> threeOPTOperation(int i, int j, int k, int mask) {
		bool Swap = static_cast<bool>(mask & 1);             //bit - 0
		bool reverse1 = static_cast<bool>((mask >> 1) & 1);    //bit - 1
		bool reverse2 = static_cast<bool>((mask >> 2) & 1);    //bit - 2

		vector<city_t> newTourPath;
		if (reverse1) reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
		if (reverse2) reverse(tspTourPath.begin() + j + 1, tspTourPath.begin() + k + 1);

		for (int x = 0; x <= i; x++) newTourPath.push_back(tspTourPath[x]);
		if (!Swap) {
			for (int x = i + 1; x <= j; x++) newTourPath.push_back(tspTourPath[x]);
			for (int x = j + 1; x <= k; x++) newTourPath.push_back(tspTourPath[x]);
		} else {
			for (int x = j + 1; x <= k; x++) newTourPath.push_back(tspTourPath[x]);
			for (int x = i + 1; x <= j; x++) newTourPath.push_back(tspTourPath[x]);
		}
		for (int x = k + 1; x < N; x++) newTourPath.push_back(tspTourPath[x]);

		if (reverse1) reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
		if (reverse2) reverse(tspTourPath.begin() + j + 1, tspTourPath.begin() + k + 1);
		return newTourPath;
	}


public:
	Heuristics(CityLocation *cityLocations, int N) :
			N(N) {
		this->cityLocations = cityLocations;
		visited = new bool[N];
	}

	void NearestNeighbourHeuristic() {
		resetBuffer();

		city_t Start = rand() % N;
		city_t Last = Start;
		visited[Last] = true;
		tspTourPath.push_back(Start);

		while (tspTourPath.size() < N) {
			city_t city = findNearestUnvisited(Last);
			visited[city] = true;
			tspTourPath.push_back(city);
		}
	}

	void NearestInsertionHeuristic() {
		resetBuffer();

		city_t Start = rand() % N;
		visited[Start] = true;
		tspTourPath.push_back(Start);
		city_t Other = findNearestUnvisited(Start);
		visited[Other] = true;
		tspTourPath.push_back(Other);

		while (tspTourPath.size() < N) {
			int Size = tspTourPath.size();
			int Near = findNearestOverall();
			visited[Near] = 1;
			int Idx = findNearestEdge(Near);

			tspTourPath.push_back(Near);
			for (int i = Size - 1; i >= 0; i--) {
				if (tspTourPath[i] == Idx) break;
				swap(tspTourPath[i], tspTourPath[i + 1]);
			}
		}
	}

	void CheapestInsertionHeuristic() {
		resetBuffer();

		city_t Start = rand() % N;
		visited[Start] = true;
		tspTourPath.push_back(Start);
		city_t Other = findNearestUnvisited(Start);
		visited[Other] = true;
		tspTourPath.push_back(Other);

		while (tspTourPath.size() < N) {
			int Size = tspTourPath.size();
			double Min = numeric_limits<double>::max();
			int x = -1;
			int z = -1;

			for (int edge = 0; edge < tspTourPath.size(); edge++) {
				int xx = tspTourPath[edge];
				int yy = tspTourPath[(edge + 1) % tspTourPath.size()];
				for (int node = 0; node < N; node++) {
					if (visited[node]) continue;
					double Dist =
							cityLocations[xx].distanceWith(cityLocations[node]) +
							cityLocations[yy].distanceWith(cityLocations[node]) -
							cityLocations[xx].distanceWith(cityLocations[yy]);
					if (Dist < Min) Min = Dist, x = xx, z = node;
				}
			}
			tspTourPath.push_back(z);
			visited[z] = true;

			for (int i = Size - 1; i >= 0; i--) {
				if (tspTourPath[i] == x) break;
				swap(tspTourPath[i], tspTourPath[i + 1]);
			}
		}
	}

	void TwoOptHeuristic() {
		resetBuffer();

		NearestNeighbourHeuristic();
		while (true) {
			double Curr = calculateTourCost(tspTourPath, cityLocations);
			bool Changed = false;

			for (int i = 0; i < tspTourPath.size(); i++) {
				for (int j = i + 2; j < tspTourPath.size(); j++) {
					reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
					double NewCost = calculateTourCost(tspTourPath, cityLocations);
					if (NewCost < Curr) {
						Changed = true;
						break;
					}
					reverse(tspTourPath.begin() + i + 1, tspTourPath.begin() + j + 1);
				}
				if (Changed) break;
			}
			if (!Changed) break;
		}
	}

	void ThreeOptHeuristic() {
		resetBuffer();

		NearestNeighbourHeuristic();
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
				NearestNeighbourHeuristic();
				break;
			case NearestInsertion:
				NearestInsertionHeuristic();
				break;
			case CheapestInsertion:
				CheapestInsertionHeuristic();
				break;
			case TwoOPT:
				TwoOptHeuristic();
				break;
			case ThreeOPT:
				ThreeOptHeuristic();
				break;
		}

		return tspTourPath;
	}

	virtual ~Heuristics() {
		delete[] visited;
	}
};


#endif //TSP_HEURISTICS_H
