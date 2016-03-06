#define HEADER_H
//#define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
#define REP(i,n)	for(auto i=decltype(n)(0); i<(n); ++i)
#define all(v)		begin(v), end(v)
using namespace std;		using ull= unsigned long long;
using ll = long long;		using ld = long double;
using vi = vector<ll>;		using vvi= vector<vi>;
using vb = vector<bool>;	using ii = pair<ll,ll>;
constexpr bool LOG = true;
void Log() { if(LOG) cerr << "\n"; }
template<class T, class... S> void Log(T t, S... s){
	if(LOG) cerr << t << "\t", Log(s...);
} /* ============== END OF HEADER ============== */

int main(int argc, char **args){

	if(argc<4){
		cout << "give #testcases, #vertices and #edges as arguments\n";
		return 0;
	}

	ll t = stoi(args[1]);
	ll n = stoi(args[2]);
	ll m = stoi(args[3]);

	bool weighted = false;
	ll max_w = 1e6;
	srand(31415);

	cerr << "program called as "<< args[0] << endl;

	if(strcmp(args[0], "./matching_weighted")==0){
		cerr << "weighted matching\n";
		cerr << "max weight: 1e6\n";
		weighted = true;
	}


	cout << t << "\n";
	for(ll tc = 0; tc < t; ++tc){
		cout << n << " " << m << "\n";

		for(ll i = 0; i < m; ++i){
			ll u = rand()%n;
			ll v = rand()%n;
			cout << u << ' ' << v;
			if(weighted){
				ll w = rand()%max_w;
				cout << ' ' << w;
			}
			cout << "\n";
		}
	}
	return 0;
}


