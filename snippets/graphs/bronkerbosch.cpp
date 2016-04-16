#include "../header.h"
constexpr size_t M = 128; using S = bitset<M>;
// count maximal cliques. Call with R=0, X=0, P[u]=1 forall u
int BronKerbosch(const vector<S> &edges, S &R, S &&P, S &&X){
	if(P.count() == 0 && X.count() == 0) return 1;
	auto PX = P | X; int p=-1;	// the last true bit is the pivot
	for(int i = M-1; i>=0; i--) if(PX[i]){ p = i; break; }
	auto mask = P & (~edges[p]); int count = 0;
	for (size_t u = 0; u < edges.size(); ++u) {
		if(!mask[u]) continue;
		R[u]=true;
		count += BronKerbosch(edges,R,P & edges[u],X & edges[u]);
		if(count > 1000) return count;
		R[u]=false; X[u]=true; P[u]=false;
	}
	return count;
}
