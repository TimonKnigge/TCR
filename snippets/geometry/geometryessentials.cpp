#define EPSILON 1e-6

// Coordinate type, change to long long or double when necessary.
typedef int coord;

struct point {
public:
    coord x, y;
    point() {}
    point(coord x, coord y) : x(x), y(y)   {}
    point(const point &p) : x(p.x), y(p.y) {}
    point operator+ (const point &p) const { return point(x + p.x, y + p.y); }
    point operator- (const point &p) const { return point(x - p.x, y - p.y); }
    point operator* (double c) const { return point((coord)(x * c), (coord)(y * c)); }
    point operator/ (double c) const { return point((coord)(x / c), (coord)(y / c)); }
    bool  operator< (const point &r) const { return (y != r.y ? 
                                                     (y < r.y) : (x > r.x)); }
    bool  operator==(const point &r) const { return (y == r.y  && x == r.x); }
};
struct line { 
    point p1, p2; 
    line() {}
    line(point p1, point p2) : p1(p1), p2(p2) {}
    line(const line &l) : p1(l.p1), p2(l.p2) {}
};
enum LineType { LINE, RAY, SEGMENT };

coord dot(point p1, point p2) { return p1.x * p2.x + p1.y * p2.y; }
coord lensq(point p1, point p2) { 
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y); 
}

coord det(coord x1, coord y1, coord x2, coord y2) { return x1 * y2 - x2 * y1; }
coord det(point p1, point p2) { return p1.x * p2.y - p1.y * p2.x; }
coord det(point p1, point p2, point origin) { 
    return (p1.x - origin.x)*(p2.y - origin.y) - (p1.y - origin.y)*(p2.x - origin.x);
}
coord det(vector<point> pts) {
    coord sum = 0;
    for(int i = 0; i < pts.size(); ++i)
        sum += det(pts[i], pts[(i + 1) % pts.size()]);
    return sum;
}

double area(point p1, point p2, point p3) { return abs(det(p1, p2, p3)) / 2.0; }
double area(vector<point> polygon) { return abs(det(polygon)) / 2.0; }

int seq(point p1, point p2, point p3) {
    coord d = det(p1, p2, p3);
    return (d < 0 ? -1:     // Right turn
            d > 0 ?  1:     // Left  turn
                     0);    // Points are colinear
}

point project(line l, point p, LineType type) {
    double lambda = dot(p - l.p1, l.p2 - l.p1)/((double)dot(l.p2 - l.p1, l.p2 - l.p1));
    switch(type){
        case LineType.SEGMENT: lambda = min(1.0, lambda);
        case LineType.RAY:     lambda = max(0.0, lambda);
        default: break;
    }
    return l.p1 + (l.p2 - l.p1) * lambda;
}

bool intersect_lines(line l1, line l2, double* lambda, LineType type) {
    // Intersection point can be reconstructed as l1.p1 + lambda * (l1.p2 - l1.p1).
    // Returns false if the lines are parallel, handle coincidence in advance.
    coord s1x, s1y, s2x, s2y;
    s1x = l1.p2.x - l1.p1.x;    s1y = l1.p2.y - l1.p1.y;
    s2x = l2.p2.x - l2.p1.x;    s2y = l2.p2.y - l2.p1.y;
    coord denom = det(s1x, s1y, s2x, s2y);
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
