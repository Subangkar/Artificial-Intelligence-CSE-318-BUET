//
// Created by subangkar on 11/25/18.
//

#ifndef NPUZZLE_NODE_H
#define NPUZZLE_NODE_H
#define BOARD_SQ_SIZE 3

//#include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

class Node {
public:
	int **A = nullptr;
	static int boardSqSize;

	friend ostream &operator<<(ostream &os, const Node &node);

	Node() {
		A = new int *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new int[boardSqSize];
			memset(A[i], 0, boardSqSize * sizeof(A[0][0]));
		}
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

	~Node() {
		if (A == nullptr) return;
		for (int i = 0; i < boardSqSize; ++i) {
			delete A[i];
		}
		delete[] A;
		A = nullptr;
	}

	bool operator==(const Node &right) const {
		for (int i = 0; i < boardSqSize; i++)
			for (int j = 0; j < boardSqSize; j++)
				if (A[i][j] != right.A[i][j]) return false;
		return true;
	}

	bool operator!=(const Node &right) const {
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

	bool isSolveAble() {

		int blank_row_no = -1;
		vector<int> arr;
		for (int i = 0; i < boardSqSize; i++)
			for (int j = 0; j < boardSqSize; j++) {
				if (A[i][j])
					arr.push_back(A[i][j]);
				else
					blank_row_no = i;
			}
		int invCount = getInvCount(arr);
		bool boardSizeOdd = static_cast<bool>(boardSqSize & 1);
//		cout << boardSizeOdd << " " << blank_row_no << " " << invCount << endl;
		if (boardSizeOdd && !(invCount & 1)) // odd-board & even-inversions
			return true;
		else if (!boardSizeOdd && ((blank_row_no + getInvCount(arr)) & 1)) // even-board & odd-sum
			return true;
		return false;
	}


	static int getInvCount(const vector<int> &arr) {
		int inv_count = 0;
		for (int i = 0; i < arr.size() - 1; i++)
			for (int j = i + 1; j < arr.size(); j++)
				if (arr[i] > arr[j])
					inv_count++;

		return inv_count;
	}
};

int Node::boardSqSize = 0;

ostream &operator<<(ostream &os, const Node &node) {
	if (!node.A) return os;
	for (int i = 0; i < Node::boardSqSize; i++) {
		for (int j = 0; j < Node::boardSqSize; j++)
			os << setw(2) << node.A[i][j] << " ";
		os << endl;
	}
	os << " ---------" << std::endl;
	return os;
}

#endif //NPUZZLE_NODE_H
