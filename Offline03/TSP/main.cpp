#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>


using namespace std;
#define MAX 105

struct Point {
	double x;
	double y;

	Point() {}

	Point(double a, double b) {
		x = a;
		y = b;
	}

	double distanceWith(Point other) { return hypot(x - other.x, y - other.y); }
};

int n;
Point pt[MAX];
bool Vis[MAX];
vector<int> Tour;

int FindNearestUnvisited(int x) {
	double Min = LLONG_MAX;
	int Idx = -1;
	for (int i = 0; i < n; i++) {
		if (Vis[i]) continue;
		if (pt[x].distanceWith(pt[i]) < Min) Min = pt[x].distanceWith(pt[i]), Idx = i;
	}
	return Idx;
}

int FindOverallNearest() {
	double Min = LLONG_MAX;
	int Idx = -1;
	for (int i = 0; i < n; i++) {
		if (!Vis[i]) continue;
		int Nearest = FindNearestUnvisited(i);
		if (pt[i].distanceWith(pt[Nearest]) < Min) Min = pt[i].distanceWith(pt[Nearest]), Idx = Nearest;
	}
	return Idx;
}

int FindNearestEdge(int node) {
	double Min = LLONG_MAX;
	int Idx = -1;
	int Size = Tour.size();
	for (int edge = 0; edge < Size; edge++) {
		int x = Tour[edge];
		int y = Tour[(edge + 1) % Size];
		double Dist = pt[x].distanceWith(pt[node]) + pt[y].distanceWith(pt[node]) - pt[x].distanceWith(pt[y]);
		if (Dist < Min) Min = Dist, Idx = x;
	}
	return Idx;
}

double Cost(vector<int> Tour) {
	double Ans = 0;
	int Size = Tour.size();
	for (int i = 0; i < Size; i++) {
		int xx = Tour[i];
		int yy = Tour[(i + 1) % Size];
		Ans += pt[xx].distanceWith(pt[yy]);
	}
	return Ans;
}

void PrintSolution(const vector<int> &Tour) {
	printf("Solution Cost : %lf\n", Cost(Tour));
	printf("Tour Description : ");
	for (int i = 0; i < Tour.size(); i++) printf("%d ", Tour[i]);
	printf("\n\n");
}

void NearestNeighbourHeuristic() {
	Tour.clear();
	memset(Vis, 0, sizeof(Vis));

	int Start = rand() % n;
	int Last = Start;
	Vis[Last] = 1;
	Tour.push_back(Start);

	while (Tour.size() < n) {
		int Idx = FindNearestUnvisited(Last);
		Vis[Idx] = 1;
		Tour.push_back(Idx);
	}
}

void NearestInsertionHeuristic() {
	Tour.clear();
	memset(Vis, 0, sizeof(Vis));

	int Start = rand() % n;
	Vis[Start] = 1;
	Tour.push_back(Start);
	int Other = FindNearestUnvisited(Start);
	Vis[Other] = 1;
	Tour.push_back(Other);

	while (Tour.size() < n) {
		int Size = Tour.size();
		int Near = FindOverallNearest();
		Vis[Near] = 1;
		int Idx = FindNearestEdge(Near);

		Tour.push_back(Near);
		for (int i = Size - 1; i >= 0; i--) {
			if (Tour[i] == Idx) break;
			swap(Tour[i], Tour[i + 1]);
		}
	}
}

void CheapestInsertionHeuristic() {
	Tour.clear();
	memset(Vis, 0, sizeof(Vis));

	int Start = rand() % n;
	Vis[Start] = 1;
	Tour.push_back(Start);
	int Other = FindNearestUnvisited(Start);
	Vis[Other] = 1;
	Tour.push_back(Other);

	while (Tour.size() < n) {
		int Size = Tour.size();
		double Min = LLONG_MAX;
		int x = -1;
		int z = -1;

		for (int edge = 0; edge < Size; edge++) {
			int xx = Tour[edge];
			int yy = Tour[(edge + 1) % Size];
			for (int node = 0; node < n; node++) {
				if (Vis[node]) continue;
				double Dist =
						pt[xx].distanceWith(pt[node]) + pt[yy].distanceWith(pt[node]) - pt[xx].distanceWith(pt[yy]);
				if (Dist < Min) Min = Dist, x = xx, z = node;
			}
		}
		Tour.push_back(z);
		Vis[z] = 1;

		for (int i = Size - 1; i >= 0; i--) {
			if (Tour[i] == x) break;
			swap(Tour[i], Tour[i + 1]);
		}
	}
}

void TwoOptHeuristic() {
	Tour.clear();
	memset(Vis, 0, sizeof(Vis));

	NearestNeighbourHeuristic();
	while (true) {
		double Curr = Cost(Tour);
		bool Changed = false;

		for (int i = 0; i < Tour.size(); i++) {
			for (int j = i + 2; j < Tour.size(); j++) {
				reverse(Tour.begin() + i + 1, Tour.begin() + j + 1);
				double NewCost = Cost(Tour);
				if (NewCost < Curr) {
					Changed = true;
					break;
				}
				reverse(Tour.begin() + i + 1, Tour.begin() + j + 1);
			}
			if (Changed) break;
		}
		if (!Changed) break;
	}
}

vector<int> Operation(int i, int j, int k, int mask) {
	bool Swap = mask & 1;             //bit - 0
	bool Reverse1 = (mask >> 1) & 1;    //bit - 1
	bool Reverse2 = (mask >> 2) & 1;    //bit - 2

	vector<int> Now;
	if (Reverse1) reverse(Tour.begin() + i + 1, Tour.begin() + j + 1);
	if (Reverse2) reverse(Tour.begin() + j + 1, Tour.begin() + k + 1);

	for (int x = 0; x <= i; x++) Now.push_back(Tour[x]);
	if (!Swap) {
		for (int x = i + 1; x <= j; x++) Now.push_back(Tour[x]);
		for (int x = j + 1; x <= k; x++) Now.push_back(Tour[x]);
	} else {
		for (int x = j + 1; x <= k; x++) Now.push_back(Tour[x]);
		for (int x = i + 1; x <= j; x++) Now.push_back(Tour[x]);
	}
	for (int x = k + 1; x < n; x++) Now.push_back(Tour[x]);

	if (Reverse1) reverse(Tour.begin() + i + 1, Tour.begin() + j + 1);
	if (Reverse2) reverse(Tour.begin() + j + 1, Tour.begin() + k + 1);
	return Now;
}

void ThreeOptHeuristic() {
	Tour.clear();
	memset(Vis, 0, sizeof(Vis));

	NearestNeighbourHeuristic();
	while (true) {
		double Curr = Cost(Tour);
		bool Changed = false;

		for (int i = 0; i < Tour.size(); i++) {
			for (int j = i + 2; j < Tour.size(); j++) {
				for (int k = j + 2; k < Tour.size(); k++) {
					for (int mask = 1; mask < 8; mask++) {
						vector<int> Now = Operation(i, j, k, mask);
						double NewCost = Cost(Now);
						if (NewCost < Curr) {
							Changed = true;
							Tour = Now;
							break;
						}
					}
					if (Changed) break;
				}
				if (Changed) break;
			}
		}
		if (!Changed) break;
	}
}

const char *heuristics_name[] = {"NearestNeighbour Heuristic", "NearestInsertion Heuristic", "CheapestInsertion Heuristic",
                                 "2-OPT Heuristic", "3-OPT Heuristic"};
void (*heuristics_functions[])() = {NearestNeighbourHeuristic, NearestInsertionHeuristic, CheapestInsertionHeuristic,
                                    TwoOptHeuristic, ThreeOptHeuristic};

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt","w", stdout);

	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> pt[i].x >> pt[i].y;

	for (int f = 0; f < 5; ++f) {
		cout << heuristics_name[f] << " :: " << endl;
		heuristics_functions[f]();
		PrintSolution(Tour);
	}

}