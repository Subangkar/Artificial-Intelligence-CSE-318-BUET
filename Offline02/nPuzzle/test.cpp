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

using namespace std;

int getInvCount(int arr[], int n) {
	int inv_count = 0;
	for (int i = 0; i < n - 1; i++)
		for (int j = i + 1; j < n; j++)
			if (arr[i] > arr[j])
				inv_count++;

	return inv_count;
}


struct S {
	int x;
	int y;

	bool operator<(const S &right) const {
		return x < right.x && y < right.y;
	}

	bool operator==(const S &rhs) const {
		return x == rhs.x &&
		       y == rhs.y;
	}

	bool operator!=(const S &rhs) const {
		return !(rhs == *this);
	}

};

//struct CustomCompare {
//	bool operator()(const pair<double, S> &lhs, const pair<double, S> &rhs) const {
//		return lhs.first < rhs.second;
//	}
//};

class ads{
public:
	double k;
	S val;

	bool operator==(const ads &rhs) const {
		return val == rhs.val;
	}

	bool operator!=(const ads &rhs) const {
		return !(rhs == *this);
	}

	bool operator<(const ads &rhs) const {
//		if (val < rhs.val)
//			return true;
//		if (rhs.k < k)
//			return false;
		return val < rhs.val;
	}

	bool operator>(const ads &rhs) const {
		return rhs < *this;
	}

	bool operator<=(const ads &rhs) const {
		return !(rhs < *this);
	}

	bool operator>=(const ads &rhs) const {
		return !(*this < rhs);
	}
};

struct Comparator
{
	bool operator() (const ads& lhs,
	                 const ads& rhs) const
	{
		if (lhs.k == rhs.k)
			return lhs.val < rhs.val;
		else
			return lhs.k < rhs.k;
	}
};

/* Driver progra to test above functions */
int main(int argv, char **args) {
//	priority_queue<pair<double,S>,CustomCompare> pq;
	set<ads,Comparator> pq;
	set<ads,Comparator>::iterator it;
	pq.insert({2.3, {3, 4}});
	pq.insert({2, {5, 7}});
	pq.insert({5.0, {3, 4}});
	pq.erase({1,{3,4}});
//	pq.find({1,{3,4}})->k=1;
//	pq.insert({1,{3,4}});
//	pq.erase()
//	pq.insert()

//	while (!pq.empty()) {
//		cout << pq.begin()->first << endl;
////		pq.pop();
//	}
	for (it = pq.begin(); it != pq.end(); ++it) {
		cout << it->k << endl;
	}

	return 0;
}