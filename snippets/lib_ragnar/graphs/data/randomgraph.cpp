#include "../../header.h"
#include <random>

int main(int count,char** args){
	ios_base::sync_with_stdio(false);
	typedef uint_fast32_t UI;
	// generate a graph with given number of nodes and size
	UI N = 100000, M = 1000000;
	bool directed = true;
	if(count > 1)
	N = atoi(args[1]); // nodes
	if(count > 2)
	M = atoi(args[2]); // edges
	if(count > 3)
	directed = false;

	// always just use [0,N) indices
	cout << N << " " << M << "\n";
	cerr << N << " " << M << "\n";

	// assumes no u-u edges
	typedef mt19937 RNG;
	RNG rng(time(0));

	set<pair<UI,UI>> edges; // don't add edges twice
	srand(time(0));
	for(auto i = 0u; i<M;i++){
		while(true){
			unsigned u = rng() % N;
			unsigned v = rng() % (N-1);
			if (v>=u)v++;
			if(!directed && u > v) swap(u,v);
			if(edges.count({u,v})>0)
				continue;
			else{
				edges.insert({u,v});
				cout << u << " " << v << "\n";
				break;
			}
		}
	}
	return 0;
}
