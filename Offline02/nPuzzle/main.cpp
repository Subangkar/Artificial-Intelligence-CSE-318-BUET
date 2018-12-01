#include "Node.h"
#include "AStarSearch.h"

#define MAX 105


void printSolution(aStarSearch &starSearch, Node &Start, Node &Goal) {
	Node now = Goal;

	//print soln
	vector<Node> Path;
	while (!(starSearch.parent[now] == now)) {
		Path.push_back(now);
		now = starSearch.parent[now];
	}
	Path.push_back(Start);
	reverse(Path.begin(), Path.end());
	for (auto &i : Path) cout << i;
}

void executeSearch(Node &Start, Node &Goal, int heuristic, bool printSol = true) {
	aStarSearch starSearch;
	starSearch.setHeuristic(heuristic);
	int nExpanded = starSearch.AStarSearch(Start, Goal);
	cout << "No of Steps: " << (int) starSearch.cost[Goal] << endl;
	cout << "No of Nodes Expanded: " << nExpanded << endl;
	cout << "No of Nodes Opened: " << starSearch.visited.size() << endl;
	cout << endl;

	if (printSol) printSolution(starSearch, Start, Goal);
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int boardSqSize = 3;
	cin >> boardSqSize;
	Node::boardSqSize = boardSqSize;
	Node Goal;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++)
			Goal.A[i][j] = i * Node::boardSqSize + j + 1;
	Goal.A[Node::boardSqSize - 1][Node::boardSqSize - 1] = 0;
	Node Start;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++) {
			cin >> Start.A[i][j];
		}
//	cout << Goal;
//	cout << Start;
//	cout << aStarSearch::ManHattan(Start, Goal) << endl;
//	cout << aStarSearch::HammingDistance(Start, Goal) << endl;
//	cout << aStarSearch::nLinearConflicts(Start, Goal) << endl;

	if (!Start.isSolveAble()) {
		cout << "No Solution" << endl;
	} else {
		{
			cout << "#ManHattan Distance Heuristics: " << endl;
			executeSearch(Start, Goal, MANHATTAN_DISTANCE, false);

			cout << "#Hamming Distance Heuristics: " << endl;
			executeSearch(Start, Goal, HAMMING_DISTANCE,false);

			cout << "#Linear Conflicts Heuristics: " << endl;
			executeSearch(Start, Goal, LINEAR_CONFLICT,false);
		}
	}
}

/*
8 2 0 5 4 7 3 6 1
*/
