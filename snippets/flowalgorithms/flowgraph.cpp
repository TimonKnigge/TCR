#include "../header.h"
using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	const int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	const F cap;	// capacity
	const W cost;	// unit cost
	S(int v, int ri, F c, W cost = 0) :
		v(v), r(ri), f(0), cap(c), cost(cost) {}
	inline F res() const { return cap - f; }
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F c, W cost = 0){ auto &t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost);
		t[v].emplace_back(u, t[u].size()-1, c, -cost);
	}
	void add_arc(int u, int v, F c, W cost = 0){ auto &t = *this;
		t[u].emplace_back(v, t[v].size(), c, cost);
		t[v].emplace_back(u, t[u].size()-1, 0, -cost);
	}
	void clear() { for (auto &E : *this) for (auto &e : E) e.f = 0LL; }
};

