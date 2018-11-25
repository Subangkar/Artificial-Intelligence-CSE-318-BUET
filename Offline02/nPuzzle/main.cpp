#include "Node.h"
#include "AStarSearch.h"

#define MAX 105


int main() {
	freopen("in.txt", "r", stdin);
//	freopen("out.txt", "w", stdout);

	int boardSqSize = 3;
	cin >> boardSqSize;
	Node::boardSqSize = boardSqSize;
	Node Goal;
	for (int i = 0; i < boardSqSize; i++) for (int j = 0; j < boardSqSize; j++) Goal.A[i][j] = i * 3 + j;
	Node Start;
	for (int i = 0; i < boardSqSize; i++)
		for (int j = 0; j < boardSqSize; j++)
			cin >> Start.A[i][j];
	aStarSearch starSearch;
	starSearch.AStarSearch(Start,Goal);
	Node now = Goal;
	vector<Node> Path;
	while (!(starSearch.parent[now] == now)) {
		Path.push_back(now);
		now = starSearch.parent[now];
	}
	Path.push_back(Start);
	reverse(Path.begin(), Path.end());
	for (auto &i : Path) i.Print();

	printf("%.0lf\n", starSearch.cost[Goal]);
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
