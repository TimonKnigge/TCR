#include "../header.h"
using F = ll; using W = ll; // types for flow and weight/cost
struct S{
	int v;			// neighbour
	const int r;	// index of the reverse edge
	F f;			// current flow
	const F cap;	// capacity
	const W cost;	// unit cost
	S(int v, int reverse_index, F capacity, W cost = 0) :
		v(v), r(reverse_index), f(0), cap(capacity), cost(cost) {}
};
struct FlowGraph : vector<vector<S>> {
	FlowGraph(size_t n) : vector<vector<S>>(n) {}
	void add_edge(int u, int v, F capacity, W cost = 0){
		operator[](u).emplace_back(v, operator[](v).size(), capacity, cost);
		operator[](v).emplace_back(u, operator[](u).size()-1, 0, -cost);
	}
};

