#include "../header.h"
# define EPSILON 1e -7

// Finds the first i s.t. arr[i]>=val, assuming that arr[l] <= val <= arr[h]
int integer_binary_search(int l, int h, vector<double> &arr, double val) {
	while (l < h) {
		int m = l + (h - l) / 2;
		if (arr[m] >= val) h = m;
		else				 l = m + 1;
	}
	return l;
}

// Given a monotonically increasing function f, approximately solves f(x)=c,
// assuming that f(l) <= c <= f(h)
double binary_search(double l, double h, double (*f)(double), double c) {
	while (true) {
		double m = (l + h) / 2, v = f(m);
		if (abs(v - c) < EPSILON) return m;
		if (v < c) l = m;
		else	   h = m;
	}
}

// Modifying binary search to do an integer ternary search:
int integer_ternary_search(int l, int h, vector <double> &arr) {
	while (l < h) {
		int m = l + (h - l) / 2;
		if (arr[m + 1] - arr[m] >= 0) h = m;
		else l = m + 1;
	}
	return l;
}
