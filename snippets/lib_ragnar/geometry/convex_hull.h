#include "../header.h"
#include "geometry_basics.h"

point pivot; // global variable

bool angle_cmp(point a, point b) { // important angle-sorting function
	if (traingle_area(pivot, a, b) == 0) // collinear
		return point_distance(pivot, a) < point_distance(pivot, b); // which one closer
	int d1x = a.x - pivot.x, d1y = a.y - pivot.y;
	int d2x = b.x - pivot.x, d2y = b.y - pivot.y;
	return (atan2((double)d1y, (double)d1x) - atan2((double)d2y, (double)d2x)) < 0;
}

vector<point> convex_hull(vector<point> polygon) {
	// polygon should have at least length 3
	// first, find P0 = point with lowest Y and if tie: rightmost X
	int i, P0 = 0, N = polygon.size();
	for (i = 1; i < N; i++)
		if (polygon[i].y < polygon[P0].y || (polygon[i].y == polygon[P0].y && polygon[i].x > polygon[P0].x))
			P0 = i;
	point temp = polygon[0]; // swap selected vertex with polygon[0]
	polygon[0] = polygon[P0];
	polygon[P0] = temp;
	// second, sort points by angle w.r.t. P0, skipping polygon [0]
	pivot = polygon[0]; // use this global variable as reference
	sort(++polygon.begin(), polygon.end(), angle_cmp);
	// third, the ccw tests
	stack<point> S;
	point prev, now;
	S.push(polygon[N - 1]); // put two starting vertices into stack S
	S.push(polygon[0]);
	i = 1; // and start checking the rest
	while (i < N) { // note: N must be >= 3 for this method to work
		now = S.top();
		S.pop();
		prev = S.top();
		S.push(now); // trick to get the 2nd item from top of S
		if (ccw(prev, now, polygon[i])) { // if these 3 points make a left turn
			S.push(polygon[i]); // accept
			i++;
		}
		else // otherwise
			S.pop(); // pop this point until we have a left turn
	}
	vector<point> ConvexHull;
	while (!S.empty()) { // from stack back to vector
		ConvexHull.push_back(S.top());
		S.pop();
	}
	ConvexHull.pop_back(); // the last one is a duplicate of first one
	return ConvexHull; // return the result
}
