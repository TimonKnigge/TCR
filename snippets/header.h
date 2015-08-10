#include <iostream>
#include <sstream>
#include <iomanip>

#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <list>
#include <bitset>
#include <tuple>

#include <algorithm>
#include <functional>

#include <string>
#include <random>	//c++11

#include <cstring>  // Include for memset!
#include <cmath>
#include <cassert>
#include <chrono>

const int INF = 2e9+1;			// 9
const long long LLINF = 9e18+1;	// 18
const long double LDINF = 1e300+1;

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<bool> vb;
typedef long long ll;
typedef long double ld;

constexpr bool LOG = true;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);
	return 0;
}
