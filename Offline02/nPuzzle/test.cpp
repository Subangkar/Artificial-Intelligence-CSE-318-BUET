////
//// Created by Subangkar on 01-Dec-18.
////
//#include <iostream>
//#include <cstring>
//#include <algorithm>
//using namespace std;
//int main(){
//	int **A = new int *[4];
//	for (int i = 0; i < 4; ++i) {
//		A[i] = new int[4];
////			for (int j = 0; j < boardSqSize; j++)
////				A[i][j] = 0;
//		std::memset(A[i], 2, 4 * sizeof(A[0][0]));
//	}
//	int **B = new int *[4];
//	for (int i = 0; i < 4; ++i) {
//		B[i] = new int[4];
//		std::memset(B[i], 2, 4 * sizeof(A[0][0]));
//	}
//
//	B[1][2] = 3;
//
//	cout << std::equal(A[1],A[1]+4,B[1]);
//
//	return 0;
//}

#include <bits/stdc++.h>
int getInvCount(int arr[], int n)
{
	int inv_count = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j])
				inv_count++;

	return inv_count;
}

/* Driver progra to test above functions */
int main(int argv, char** args)
{
	int arr[] = { 9,1,10,5,14, 8, 13, 3,2, 6, 12,15, 4, 11, 7 };
	int n = sizeof(arr) / sizeof(arr[0]);
	printf(" Number of inversions are %d \n", getInvCount(arr, n));
	return 0;
}