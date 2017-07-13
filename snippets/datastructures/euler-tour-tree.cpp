#include "../header.h"
#include "sequence.cpp"
struct EulerTourTree {
	struct edge { int u, v; };
	vector<seq<edge>> vertices;
	vector<unordered_map<int, seq<edge>>> edges;
	EulerTourTree(int n) {
		vertices.reserve(n); edges.reserve(n);
		for (int i = 0; i < n; ++i) add_vertex();
	}
		
	// Create a new vertex.
	int add_vertex() {
		int id = (int)vertices.size();
		vertices.push_back(edge{id, id});
		edges.emplace_back();
		return id;
	}
	// Find root of the subtree containg this vertex.
	int root(int u) { return vertices[u].root()->min()->val.u; }
	bool same(int u, int v) { return vertices[u].root()==vertices[v].root(); }
	int size(int u) { return (vertices[u].root()->size_ + 2) / 3; }
	// Make v the parent of u. Assumes u has no parent!
	void attach(int u, int v) {
		seq<edge> *i1, *i2;
		tie(i1, i2) = split(vertices[v].root(), &vertices[v]);
		::merge(i1,
				&(edges[v].emplace(u, seq<edge>{edge{v, u}}).first)->second,
				vertices[u].root(),
				&(edges[u].emplace(v, seq<edge>{edge{u, v}}).first)->second,
				i2);
	}
	// Reroot the tree containing u at u.
	void reroot(int u) {
		seq<edge> *i1, *i2;
		tie(i1, i2) = split(vertices[u].root(), &vertices[u]);
		merge(i2, i1);
	}
	// Links u and v.
	void link(int u, int v) { reroot(u); attach(u, v); }
	// Cut {u, v}. Assumes it exists!!
	void cut(int u, int v) {
		auto uv = edges[u].find(v), vu = edges[v].find(u);
		if (uv->second.index() > vu->second.index()) swap(u, v), swap(uv, vu);
		seq<edge> *i1, *i2;
		tie(i1, i2) = split(vertices[u].root(), &uv->second);
		i2 = split(i2, 1).second;
		i2 = split(i2, &vu->second).second;
		i2 = split(i2, 1).second;
		merge(i1, i2);
		edges[u].erase(uv); edges[v].erase(vu);
	}
};

