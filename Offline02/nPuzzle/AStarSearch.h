//
// Created by subangkar on 11/25/18.
//
#include "Node.h"


#ifndef NPUZZLE_ASTARSEARCH_H
#define NPUZZLE_ASTARSEARCH_H
#define ZERO 0

#define MANHATTAN_DISTANCE 1
#define HAMMING_DISTANCE 2
#define LINEAR_CONFLICT 3

#define LIMIT_DEPTH 48


class aStarSearch {
public:
//	map<Node, bool> visited;
	map<Node, double> cost;
//	map<Node, Node> parent;
	map<Node, int> parent;

	size_t openedCount;

	int heuristicType = NULL;

	bool isValid(int x, int y) { return x >= 0 && y >= 0 && x < Node::boardSqSize && y < Node::boardSqSize; }

	static double HammingDistance(const Node &a, const Node &b) {
		int conflicts = 0;
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (a.A[i][j] && a.A[i][j] != b.A[i][j])conflicts++;
		return conflicts;
	}

	static double ManHattan(const Node &a, const Node &b) {
		int sum = 0;
		int pR[(Node::boardSqSize * Node::boardSqSize) + 1];
		int pC[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int r = 0; r < Node::boardSqSize; r++) {
			for (int c = 0; c < Node::boardSqSize; c++) {
				pR[a.A[r][c]] = r;
				pC[a.A[r][c]] = c;
			}
		}
		for (int r = 0; r < Node::boardSqSize; r++)
			for (int c = 0; c < Node::boardSqSize; c++)
				if (b.A[r][c])
					sum += abs(pR[b.A[r][c]] - r) + abs(pC[b.A[r][c]] - c);
		return sum;
	}

	static double nLinearConflicts(const Node &a, const Node &b) {
		int conflicts = 0;
		int pR[(Node::boardSqSize * Node::boardSqSize) + 1];
		int pC[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int r = 0; r < Node::boardSqSize; r++) {
			for (int c = 0; c < Node::boardSqSize; c++) {
				pR[a.A[r][c]] = r;
				pC[a.A[r][c]] = c;
			}
		}

		// row conflicts - @checked_okay
		for (int r = 0; r < Node::boardSqSize; r++) {
			for (int cl = 0; cl < Node::boardSqSize; cl++) {
				for (int cr = cl + 1; cr < Node::boardSqSize; cr++) {
					if (b.A[r][cl] && b.A[r][cr] && r == pR[b.A[r][cl]] && pR[b.A[r][cl]] == pR[b.A[r][cr]] &&
					    pC[b.A[r][cl]] > pC[b.A[r][cr]]) {
						conflicts++;
//						cout << b.A[r][cl] << " " << b.A[r][cr] << endl;
//						cout << pC[b.A[r][cl]] << " " << pC[b.A[r][cr]] << endl;
					}
				}
			}
		}

		// column conflicts -
		for (int c = 0; c < Node::boardSqSize; c++) {
			for (int rU = 0; rU < Node::boardSqSize; rU++) {
				for (int rD = rU + 1; rD < Node::boardSqSize; rD++) {
					if (b.A[rU][c] && b.A[rD][c] && c == pC[b.A[rU][c]] && pC[b.A[rU][c]] == pC[b.A[rD][c]] &&
					    pR[b.A[rU][c]] > pR[b.A[rD][c]]) {
						conflicts++;
//						cout << b.A[rU][c] << " " << b.A[rD][c] << endl;
//						cout << pR[b.A[rU][c]] << " " << pR[b.A[rD][c]] << endl;
					}
				}
			}
		}

		return conflicts;
	}

	static double LinearConflicts(const Node &a, const Node &b) {
		return ManHattan(a, b) + 2 * nLinearConflicts(a, b);
	}

	double Heuristic(const Node &a, const Node &b) {
		if (heuristicType == HAMMING_DISTANCE) return HammingDistance(a, b);
		if (heuristicType == MANHATTAN_DISTANCE) return ManHattan(a, b);
		if (heuristicType == LINEAR_CONFLICT) return LinearConflicts(a, b);
		return 0;
	}

	int AStarSearch(Node Start, const Node &Goal) {
		int nExpanded = 0;

		priority_queue<pair<double, Node> > openList;
		map<Node, bool> visited;
//		set<Node> visited;
		openList.push({0, Start});
		visited[Start] = true;
		cost[Start] = 0;
		parent[Start] = EOF;

		while (!openList.empty()) {
			Node u = openList.top().second;
			openList.pop();
			++nExpanded;

			if (u == Goal) {
				openedCount = visited.size();
				visited.clear();
				return nExpanded;
			}

			if (cost[u] > LIMIT_DEPTH) {
				cout << "Height limit Exceeded @" << endl << u;
				openedCount = visited.size();
				visited.clear();
				break;
			}

			int zX = 0, zY = 0;
			for (int i = 0; i < Node::boardSqSize; i++)
				for (int j = 0; j < Node::boardSqSize; j++)
					if (u.A[i][j] == ZERO)zX = i, zY = j;

			for (int Mov = 0; Mov < 4; Mov++) {
				int xx = zX + dirX[Mov];
				int yy = zY + dirY[Mov];
				if (isValid(xx, yy)) {
//					cout <<xx <<" -- " << yy << endl;
					Node v = u;
					swap(v.A[zX][zY], v.A[xx][yy]);
					double newCost = cost[u] + 1;

					if (visited.find( v ) == visited.end() || newCost < cost[v]) {

						visited[v] = true;
						cost[v] = newCost;
						parent[v] = Node::oppositeDirection(Mov);
						double Priority = newCost + Heuristic(v, Goal);
						openList.push({-Priority, v});
					}
				}
			}

		}
//		parent.clear();
		return nExpanded;
	}

	void setHeuristic(int heuristic = MANHATTAN_DISTANCE) {
		heuristicType = heuristic;
	}

	virtual ~aStarSearch() {
		heuristicType = NULL;
//		visited.clear();
		parent.clear();
		cost.clear();
	}
};

#endif //NPUZZLE_ASTARSEARCH_H
