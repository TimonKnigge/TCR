#include "../header.h"
#include "geometry_basics.h"

int determinant(vector<point> P) {
	int result = 0, x1, y1, x2, y2;
	for (size_t i = 0; i < P.size(); i++) {
		x1 = P[i].x;
		x2 = P[(i + 1) % P.size()].x;
		y1 = P[i].y;
		y2 = P[(i + 1) % P.size()].y;
		result += (x1 * y2 - x2 * y1);
	}
	return result;
}

double polygon_area(vector<point> P) {
	return abs(determinant(P)) / 2.0;
}

double polygon_perimeter(vector<point> P) {
	double result = 0.0, x1, y1, x2, y2, dx, dy;
	for (size_t i = 0; i < P.size(); i++) {
		x1 = P[i].x;
		x2 = P[(i + 1) % P.size()].x;
		y1 = P[i].y;
		y2 = P[(i + 1) % P.size()].y;
		dx = x2 - x1;
		dy = y2 - y1;
		result += sqrt(dx * dx + dy * dy);
	}
	return result;
}
