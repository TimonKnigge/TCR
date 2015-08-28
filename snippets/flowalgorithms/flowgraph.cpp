#include "../header.h"

struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	ll f;			// current flow
	const ll cap;	// capacity
	const ll cost;	// unit cost
	S(int v, int r, int c, int cost = 0) :
		v(v), r(r), f(0), cap(c), cost(cost) {}
};
using FlowGraph = vector<vector<S>>;

