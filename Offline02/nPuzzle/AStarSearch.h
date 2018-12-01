//
// Created by subangkar on 11/25/18.
//

#ifndef NPUZZLE_ASTARSEARCH_H
#define NPUZZLE_ASTARSEARCH_H
#define ZERO 0

#include "Node.h"

class aStarSearch {
public:
	map<Node, bool> visited;
	map<Node, double> cost;
	map<Node, Node> parent;

	int dirX[4] = {0, 0, 1, -1};
	int dirY[4] = {1, -1, 0, 0};

	bool isValid(int x, int y) { return x >= 0 && y >= 0 && x < Node::boardSqSize && y < Node::boardSqSize; }

	double MIsplaced(const Node &a, const Node &b) {
		double Ans = 0;
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (a.A[i][j] && a.A[i][j] != b.A[i][j])Ans++;
		return Ans;
	}

	double ManHattan(const Node &a, const Node &b) {
		double Ans = 0;
		int pX[(Node::boardSqSize * Node::boardSqSize) + 1];
		int pY[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				pX[a.A[i][j]] = i, pY[a.A[i][j]] = j;
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (b.A[i][j])
					Ans += abs(pX[b.A[i][j]] - i) + abs(pY[b.A[i][j]] - j);
		return Ans;
	}

	double Euclidean(const Node &a, const Node &b) {
		double Ans = 0;
		int pX[(Node::boardSqSize * Node::boardSqSize) + 1];
		int pY[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				pX[a.A[i][j]] = i, pY[a.A[i][j]] = j;
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (b.A[i][j])
					Ans += hypot(pX[b.A[i][j]] - i, pY[b.A[i][j]] - j);
		return Ans;
	}

	double OutOfRowColumn(const Node &a, const Node &b) {
		double Ans = 0;
		int pX[(Node::boardSqSize * Node::boardSqSize) + 1];
		int pY[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				pX[a.A[i][j]] = i, pY[a.A[i][j]] = j;
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (b.A[i][j])
					Ans += (pX[b.A[i][j]] != i) + (pY[b.A[i][j]] != j);
		return Ans;
	}

	double nMaxSwap(const Node &a, const Node &b) {
		int P[(Node::boardSqSize * Node::boardSqSize) + 1];
		int B[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				P[i * 3 + j] = a.A[i][j];
		for (int i = 0; i < 9; i++) B[P[i]] = i;

		double Ans = 0;
		// problem here
		while (P[B[0]] != P[B[B[0]]]) {
			Ans++;
			swap(P[B[0]], P[B[B[0]]]);
			swap(B[0], B[B[0]]);
		}
		cout << "Ok" << endl;
		return Ans;
	}

	int HType = 2;

	double Heuristic(const Node &a, const Node &b) {
		if (HType == 1) return MIsplaced(a, b);
		else if (HType == 2) return ManHattan(a, b);
		else if (HType == 3) return Euclidean(a, b);
		else if (HType == 4) return OutOfRowColumn(a, b);
		else return nMaxSwap(a, b);
	}

	void AStarSearch(Node Start, const Node &Goal) {
		priority_queue<pair<double, Node> > pq;
		pq.push({0, Start});
		visited[Start] = true;
		cost[Start] = 0;
		parent[Start] = Start;

		while (!pq.empty()) {
			Node u = pq.top().second;
			pq.pop();

			if (u == Goal) return;

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
					double NewCost = cost[u] + 1;

					if (!visited[v] || NewCost < cost[v]) {

						visited[v] = true;
						cost[v] = NewCost;
						parent[v] = u;
						double Priority = NewCost + Heuristic(v, Goal);
						pq.push({-Priority, v});
					}
				}
			}

		}
		parent.clear();
	}

};

#endif //NPUZZLE_ASTARSEARCH_H
