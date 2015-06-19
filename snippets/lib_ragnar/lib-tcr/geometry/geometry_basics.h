struct point { int x, y; };
struct line { point p1, p2; };

int traingle_area(point a, point b, point c);
// are p, q and r in counter-clockwise order?
int ccw(point p, point q, point r);
int point_distance(point a, point b);
int intersect(line line1, line line2);
