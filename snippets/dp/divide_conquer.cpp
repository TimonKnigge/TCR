#include "../header.h"
// dp[k][i] = min_{j<i}{dp[k-1][j]+C[j][i]}
// when A[k][i] <= A[k][i+1]
// d:old, dp: new, calculate dp[l,r] with optimum in [optl,optr]
void compute(vi &d, vi& dp, ll l, ll r, ll optl, ll optr, ll C(ll,ll)){
	ll m = (l+r)/2; ii best{1e18, -1}; // calc dp[m]
	for(ll j = min(optr, m - 1); j >= optl; --j) best = min(best,{d[j]+C(j,m),j});
	dp[m] = best.first; ll opt = best.second;
	if(l<m) compute(d,dp,l,m-1,optl,opt ,C);
	if(m<r) compute(d,dp,m+1,r,opt ,optr,C);
}
vi divide_conquer_dp(vi &d, ll C(ll,ll)){
	vi dp(d.size(), 1e18);
	compute(d,dp,0,d.size()-1,0,d.size()-1, C);
	return dp;
}
