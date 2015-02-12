point pivot;

bool angle_compare(point p1, point p2) {
    if (det(pivot, a, b) == 0) return lensq(pivot, a) < lensq(pivot, b);
    int d1x = a.x - pivot.x, d1y = a.y - pivot.y,
        d2x = b.x - pivot.x, d2y = b.y - pivot.y;
    return (atan2((double)d1y, (double)d1x) - atan2((double)d2y, (double)d2x)) < 0;
}

vector<point> graham_scan(vector<point> pts) {
    int i, P0 = 0, N = pts.size();
    for (i = 1; i < N; ++i) {
        if (pts[i] < pts[P0].y) P0 = i;
    }
    pivot = pts[P0];
    pts[P0] = pts[0];
    pts[0] = pivot;
    sort(++pts.begin(), pts.end(), angle_compare);
    
    stack<point> S;
    point prev, now;
    S.push(pts[N - 1]);
    S.push(pts[0]);
    i = 1;
    while (i < N) { // Requires 3+ points to work
        now = S.top(); S.pop();
        prev = S.top(); S.push(now);
        if (seq(prev, now, pts[i]) > 0) { // Change to >= to allow colinear points
            S.push(pts[i]);
            i++;
        } else S.pop();
    }
    
    vector<point> ch_pts;
    while(!S.empty()) ch_pts.push_back(S.top()); S.pop();
    ch_pts.pop_back();
    return ch_pts;
}