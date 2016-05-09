#include "../header.h"
#include "../geometry/essentials.cpp"	// for Point and ccw
ld eval(P p, ld x){ return x*p.x + p.y; }
// dp[k][i] = min_{j<i} (a[j]*x[i] + dp[k-1][j]=b) + c[i]
// a[j+1] < a[j], x[i+1] > x[i] (otherwise sort on x before evaluate)
// prefill dp with INF
void convex_hull_dp_2d(vi &a, vi &x, vi &b, vi &c, ll k, vi &dp){
	vector<P> v; ll n=x.size(), q=0;
	for(ll i=k-1; i<n; ++i){	// -1 only when k is 1-based
		P p(a[i-1], b[i-1]);
		while(v.size()>=2 && ccw(v[v.size()-2],v.back(),p)>0) v.pop_back();
		v.push_back(p);
		while(q+1<v.size() && eval(v[q+1],x[i]) < eval(v[q], x[i])) ++q;
		dp[i] = eval(v[q], x[i]) + c[i];
	}
}
// dp[i] = min_{j<i} (a[j]*x[i] + dp[j]) + c[i], dp[0] = c[0]
// a[j+1] < a[j], x[i+1] > x[i]
void convex_hull_dp_1d(vi &a, vi &x, vi &c, vi &dp){
	dp.assign(x.size(), 1e18); dp[0] = c[0];
	convex_hull_dp_2d(a,x,dp,c,2,dp);
}
