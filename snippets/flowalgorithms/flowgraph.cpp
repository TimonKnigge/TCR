#include "../header.h"

struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	ll f;			// current flow
	const ll cap;	// capacity
	const ll cost;	// unit cost
};
using FlowGraph = vector<vector<S>>;

