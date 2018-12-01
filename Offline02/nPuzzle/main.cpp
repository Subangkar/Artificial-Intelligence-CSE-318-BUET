#include "Node.h"
#include "AStarSearch.h"

#define MAX 105


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
	cout << Goal;
	cout << Start;
//	cout << aStarSearch::ManHattan(Start, Goal) << endl;
//	cout << aStarSearch::HammingDistance(Start, Goal) << endl;
	cout << aStarSearch::nLinearConflicts(Start, Goal) << endl;

	if (!Start.isSolveAble()) {
		cout << "No Solution" << endl;
	} else {
		aStarSearch starSearch;
		starSearch.setHeuristic(MANHATTAN_DISTANCE);
		int nExpanded = starSearch.AStarSearch(Start, Goal);
		Node now = Goal;

		cout << "No of Steps: " << (int) starSearch.cost[Goal] << endl;
		cout << "No of Nodes Expanded: " << nExpanded << endl;
		cout << "No of Nodes Opened: " << starSearch.visited.size() << endl;
		cout << endl;

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
}

/*
8 2 0 5 4 7 3 6 1
*/
