//
// Created by Subangkar on 01-Dec-18.
//
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int main(){
	int **A = new int *[4];
	for (int i = 0; i < 4; ++i) {
		A[i] = new int[4];
//			for (int j = 0; j < boardSqSize; j++)
//				A[i][j] = 0;
		std::memset(A[i], 2, 4 * sizeof(A[0][0]));
	}
	int **B = new int *[4];
	for (int i = 0; i < 4; ++i) {
		B[i] = new int[4];
		std::memset(B[i], 2, 4 * sizeof(A[0][0]));
	}

	B[1][2] = 3;

	cout << std::equal(A[1],A[1]+4,B[1]);

	return 0;
}