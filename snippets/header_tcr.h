//lstlistings skips the first [this] line
//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
//iostream string sstream vector list set map queue stack bitset
//tuple cstdio numeric iterator algorithm cmath chrono cassert
using namespace std;	// :s/ /\r/g  :s/\w*/#include <\0>/g
#define REP(i,n)	for(auto i = decltype(n)(0); i<(n); i++)
#define all(x)		x.begin(), x.end()
using ll = long long; using ld = long double; using vi = vector<ll>;
const bool LOG = false; void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...); }
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); return 0; }
