#include <chrono>
#include "Node.h"
#include "AStarSearch.h"

#define MAX 105


void printSolution(aStarSearch &starSearch, const Node &Start, const Node &Goal) {
	auto now = Goal;

	//print soln
	vector<Node> Path;
	while (starSearch.visited[now].parent_ != EOF) {
		Path.push_back(now);
		now = now.getNode(starSearch.visited[now].parent_);
	}
	Path.push_back(Start);
	reverse(Path.begin(), Path.end());
	for (auto &i : Path) cout << i;
}

void executeSearch(const Node &Start, const Node &Goal, int heuristic, bool printSol = true) {

	auto *starSearch = new aStarSearch();
	starSearch->setHeuristic(heuristic);
	auto startTime = chrono::steady_clock::now();
	int nExpanded = starSearch->AStarSearch(Start, Goal);
	auto endTime = chrono::steady_clock::now();

	auto diff = endTime - startTime;
	cout << "No of Steps: " << (int) starSearch->visited[Goal].cost_ << endl;
	cout << "No of Nodes Expanded: " << nExpanded << endl;
	cout << "No of Nodes Opened: " << starSearch->openedCount << endl;
	cout << "Execution Time: " << chrono::duration<double, milli>(diff).count() << "ms" << endl;
	cout << endl;

	if (printSol) printSolution(*starSearch, Start, Goal);
	delete starSearch;
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
		for (int j = 0; j < boardSqSize; j++)
			cin >> Start.A[i][j];

	cout << "Start: \n" << Start;
	cout << "Goal: \n" << Goal;
//	cout << aStarSearch::ManHattan(Start, Goal) << endl;
//	cout << aStarSearch::HammingDistance(Start, Goal) << endl;
//	cout << aStarSearch::nLinearConflicts(Start, Goal) << endl;

	if (!Start.isSolveAble()) {
		cout << "No Solution" << endl;
	} else {
		{
			cout << "# ManHattan Distance Heuristics: " << endl;
			executeSearch(Start, Goal, MANHATTAN_DISTANCE, false);

			cout << "# Linear Conflicts Heuristics: " << endl;
			executeSearch(Start, Goal, LINEAR_CONFLICT, false);

//			cout << "#Hamming Distance Heuristics: " << endl;
//			executeSearch(Start, Goal, HAMMING_DISTANCE,false);
		}
	}
}

/*
8 2 0 5 4 7 3 6 1
*/
