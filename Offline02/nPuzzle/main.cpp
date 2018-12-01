#include "Node.h"
#include "AStarSearch.h"

#define MAX 105


int getInvCount(const vector<int>& arr) {
	int inv_count = 0;
	for (int i = 0; i < arr.size()-1; i++)
		for (int j = i + 1; j < arr.size(); j++)
			if (arr[i] > arr[j])
				inv_count++;

	return inv_count;
}

int main() {
	freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	int boardSqSize = 3;
	cin >> boardSqSize;
	Node::boardSqSize = boardSqSize;
//	int inp[(boardSqSize * boardSqSize)];
	Node Goal;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++)
			Goal.A[i][j] = i * Node::boardSqSize + j;
	Node Start;
	vector<int> inp;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++) {
			cin >> Start.A[i][j];
			if (Start.A[i][j])
				inp.push_back(Start.A[i][j]);
		}
	if (!Start.isSolveAble()) {
		cout << "No Solution" << endl;
		return 0;
	}
	aStarSearch starSearch;
	starSearch.AStarSearch(Start, Goal);
	Node now = Goal;
	if (starSearch.parent.empty()) {
	} else {
		vector<Node> Path;
		while (!(starSearch.parent[now] == now)) {
			Path.push_back(now);
			now = starSearch.parent[now];
		}
		Path.push_back(Start);
		reverse(Path.begin(), Path.end());
		for (auto &i : Path) cout << i;

		printf("%.0lf\n", starSearch.cost[Goal]);
	}
}

/*
8 2 0 5 4 7 3 6 1
*/

//
//int main(){
//	freopen("in.txt", "r", stdin);
//	Node::boardSqSize=3;
//	Node Start;
//	for(int i=0;i<3;i++) for(int j=0;j<3;j++) scanf("%d",&Start.A[i][j]);
//
//	Node Goal;
//	for(int i=0;i<3;i++) for(int j=0;j<3;j++) Goal.A[i][j]=i*3+j;
//
//	AStarSearch(Start,Goal);
//
//	Node now=Goal;
//	vector<Node>Path;
//	while(!(parent[now]==now)) {Path.push_back(now); now=parent[now];}
//	Path.push_back(Start);
//	reverse(Path.begin(),Path.end());
//	for(int i=0;i<Path.size();i++) Path[i].Print();
//
//	printf("%.0lf\n",cost[Goal]);
//}
