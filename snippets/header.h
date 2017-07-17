#ifndef HEADER_H
#define HEADER_H
//#define _GLIBCXX_DEBUG
constexpr bool LOG = false;

#include <algorithm>
#include <bitset>
#include <cassert>
#include <chrono>
#include <cmath>
#include <complex>
#include <cstdio> // utils
#include <cstring>
#include <iostream> // strings/streams
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <tuple> // quick compare
#include <unordered_map>
#include <unordered_set>
#include <vector> // datastructures

#define REP(i, n) for(auto i = decltype(n)(0); i < (n); i++)
#define all(v) begin(v), end(v)

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using ii = pair<ll, ll>;
using vi = vector<ll>;
using vii = vector<ii>;
using vb = vector<bool>;
using vvi = vector<vi>;
using vvii = vector<vii>;

constexpr int INF = 1e9 + 1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18 + 1;
void Log() {
	if(LOG) cerr << "\n";
}
template <class T, class... S>
void Log(T t, S... s) {
	if(LOG) cerr << t << "\t", Log(s...);
}
#endif
