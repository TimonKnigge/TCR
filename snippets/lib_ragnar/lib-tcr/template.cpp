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
#include <math.h>
#include <chrono>
#include <assert.h>

#define REP(i,n)	for(decltype(n) i(0); i<(n); i++)
#define ITER(i,v)	for(auto&& i : v) // may be non-const!
#define ITERI(it,v)	for(auto it = begin(v); it != end(v);it++)
#define F(v)		begin(v), end(v)

using namespace std;
using vi = vector<int>;
constexpr int INF = 1e9;
constexpr long long LLINF = 1e18;


constexpr bool LOG = false;
template<class T> void Log(T t){if(LOG) cerr << t << "\n";}
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t <<"\t", Log(s...);
}
/* ============== END OF HEADER ============== */

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0);
	return 0;
}

