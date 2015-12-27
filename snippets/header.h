#ifndef HEADER_H
#define HEADER_H
//#define _GLIBCXX_DEBUG
constexpr bool LOG = false;

#include <iostream> // strings/streams
#include <string>
#include <sstream>
#include <vector> // datastructures
#include <list>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <bitset>
#include <tuple> // quick compare
#include <cstdio> // utils
#include <numeric>
#include <iterator>
#include <algorithm>
#include <cmath>
#include <chrono>
#include <cassert>

#define REP(i,n)	for(auto i = decltype(n)(0); i<(n); i++)
#define F(v)		begin(v), end(v)

using namespace std;
using ll = long long;
using ld = long double;
using ii = pair<ll,ll>;
using vi = vector<ll>;
using vb = vector<bool>;
using vvi = vector<vi>;

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
}
#endif
