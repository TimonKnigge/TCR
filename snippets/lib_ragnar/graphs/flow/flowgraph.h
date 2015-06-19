#include "header.h"

struct S{
	int v;	// neighbour
	int r;	// index of the reverse edge
	ll f;	// current flow
	ll cap;	// capacity
	ll cost;	// unit cost
};
using Graph = vector<vector<S>>;

