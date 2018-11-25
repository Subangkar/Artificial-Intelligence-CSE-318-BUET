//
// Created by subangkar on 11/25/18.
//

#ifndef NPUZZLE_NODE_H
#define NPUZZLE_NODE_H
#define BOARD_SQ_SIZE 3

#include<bits/stdc++.h>

using namespace std;

class Node {
public:
	int **A = nullptr;
//	int boardSqSize;
	static int boardSqSize;

	explicit Node() {
		A = new int *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new int[boardSqSize];
			memset(A[i], 0, boardSqSize * sizeof(A[0][0]));
		}
	}

	bool operator==(const Node &right) {
		for (int i = 0; i < boardSqSize; i++)
			for (int j = 0; j < boardSqSize; j++)
				if (A[i][j] != right.A[i][j]) return false;
		return true;
	}

	bool operator!=(const Node &right) {
		return !(*this == right);
	}

	bool operator<(const Node &right) const {
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				if (A[i][j] < right.A[i][j]) return true;
				else if (A[i][j] == right.A[i][j]) continue;
				else return false;
			}
		}
		return false;
	}

	void Print() {
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) std::cout << A[i][j] << " ";
			std::cout << std::endl;
		}
		std::cout << " ---------" << std::endl;
	}

	virtual ~Node() {
//		return;
		if (A == nullptr) return;
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new int[boardSqSize];
		}
		delete[] A;
		A = nullptr;
	}

	Node(const Node &node) {
		this->~Node();
		A = new int *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new int[boardSqSize];
		}
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				A[i][j] = node.A[i][j];
			}
		}
	}

	Node &operator=(const Node &node) {
		this->~Node();
		A = new int *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new int[boardSqSize];
		}
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				A[i][j] = node.A[i][j];
			}
		}
		return *this;
	}
};

int Node::boardSqSize = 0;
#endif //NPUZZLE_NODE_H
