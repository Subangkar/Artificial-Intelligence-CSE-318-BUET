//
// Created by Subangkar on 25-Dec-18.
//

#ifndef TSP_TSPDS_H
#define TSP_TSPDS_H

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <queue>


using namespace std;

typedef int city_t;
typedef vector<city_t> tsptourpath_t;

struct CityLocation {
	double x;
	double y;

	CityLocation() { x = y = 0; }

	CityLocation(double x, double y) : x(x), y(y) {}

	double distanceWith(const CityLocation &second) { return hypot(x - second.x, y - second.y); }

	double operator-(const CityLocation &right) { return hypot(x - right.x, y - right.y); }

	friend ostream &operator<<(ostream &os, const CityLocation &location) {
		os << "x: " << location.x << " y: " << location.y;
		return os;
	}
};


#endif //TSP_TSPDS_H
