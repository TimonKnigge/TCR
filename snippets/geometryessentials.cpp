#define EPSILON 1e-6

// Coordinate type, change to long long or double when necessary
typedef int ctype;

struct point   { ctype x, y; };
struct line    { point p1, p2; };

ctype det(ctype x1, ctype y1, ctype x2, ctype y2) { return x1 * y2 - x2 * y1; }
ctype det(point p1, point p2) { return p1.x * p2.y - p1.y * p2.x; }
ctype det(point p1, point p2, point origin) { 
    return (p1.x - origin.x)*(p2.y - origin.y) - (p1.y - origin.y)*(p2.x - origin.x);
}
ctype det(vector<point> pts) {
    ctype sum = 0;
    for(int i = 0; i < pts.size(); ++i)
        sum += det(pts[i], pts[(i + 1) % pts.size()]);
    return sum;
}

double area(point p1, point p2, point p3) { return abs(det(p1, p2, p3)) / 2.0; }
double area(vector<point> polygon) { return abs(det(polygon)) / 2.0; }

int seq(point p1, point p2, point p3) {
    ctype d = det(p1, p2, p3);
    return (d < 0 ? -1:     // Right turn
            d > 0 ?  1:     // Left  turn
                     0);    // Points are colinear
}

enum LineType { LINE, RAY, SEGMENT };
bool intersectLines(line l1, line l2, double* lambda, LineType type) {
    // Intersection point can be reconstructed as l1.p1 + lambda * (l1.p2 - l1.p1).
    // Returns false if the lines are parallel, handle coincidence in advance.
    ctype s1x, s1y, s2x, s2y;
    s1x = l1.p2.x - l1.p1.x;    s1y = l1.p2.y - l1.p1.y;
    s2x = l2.p2.x - l2.p1.x;    s2y = l2.p2.y - l2.p1.y;
    ctype denom = det(s1x, s1y, s2x, s2y);
    if (denom == 0) return false;
    else{
        double l = det(s1x, s1y, l1.p1.x - l2.p1.x, l1.p1.y - l2.p1.y)/((double)denom),
               m = det(s2x, s2y, l1.p1.x - l2.p1.x, l1.p1.y - l2.p1.y)/((double)denom);
        switch(type){
            case LineType.SEGMENT:  if(l > 1 || m > 1) return false;
            case LineType.RAY:      if(l < 0 || m < 0) return false;
            default: break;
        }
        *lambda = l;
        return true;
    }
}