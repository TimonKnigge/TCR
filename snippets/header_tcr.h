//lstlistings skips the first [this] line
iostream string sstream vector list set map unordered_map queue stack bitset
tuple cstdio numeric iterator algorithm cmath chrono cassert unordered_set
using namespace std;	// :s/ /\r/g  :s/\w*/#include <\0>/g
#define REP(i,n)	for(auto i = decltype(n)(0); i<(n); i++)
using ll = long long; using vi = vector<int>;
constexpr int  INF = 1e9+1; // < 1e9 - -1e9
constexpr ll LLINF = 1e18+1;
bool LOG = false;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
}
int main(){
	ios::sync_with_stdio(false); cin.tie(nullptr);
	return 0;
}
