#include "../header.h"
struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	ll f;			// current flow
	const ll cap;	// capacity
	const ll cost;	// unit cost
	S(int v, int reverse_index, ll capacity, ll cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, ll capacity, ll cost = 0){
		operator[](u).emplace_back(v, operator[](v).size(), capacity, cost);
		operator[](v).emplace_back(u, operator[](u).size()-1, 0, -cost);
	}
};

