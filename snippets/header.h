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
constexpr bool LOG =
#ifdef _LOG
true;
#define _GLIBCXX_DEBUG
#else
false;
#endif

using namespace std;
using ll = long long;
using ii = pair<int,int>;
using vi = vector<int>;
using vvi = vector<vi>;

constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
}

int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	return 0;
}
