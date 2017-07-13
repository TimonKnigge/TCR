#include "../header.h"
#include "sequence.cpp"

struct EulerTourForest {
	struct T {
		int u, v; // edge from u to v
	};
	using node = seq<T>;
	// An edge_handler is returned when creating a vertex.
	// This has to passed back in to delete the edge
	using ptr = std::unique_ptr<node>;
	using edge_handler = array<ptr, 2>;
	vector<node> nodes; // one node for each vertex

	// Create a new vertex.
	int add_vertex() {
		int v = nodes.size();
		nodes.emplace_back(T{v, v});
		return v;
	}
	// Find root of the subtree containing this vertex.
	int root(int v) { return nodes[v].root()->min()->val.u; }
	// make v the root of the tree
	void make_root(node *x) {
		// xxx v yyy -> v yyy xxx
		if(x->p == nullptr) return;
		auto[left, right] = split(x->root(), x); // left: xxx, right: v yyy
		merge(right, left);
	}
	void make_root(int v) { make_root(&nodes[v]); }

	// Cut from parent (if exists).
	void cut(edge_handler &&e) {
		if(e[0]->index() > e[1]->index()) swap(e[0], e[1]);
		// (xxx e0 yyy e1 zzz) -> (xxx zzz, yyy)
		auto xeyez = e[0]->root();
		auto[x, eyez] = split(xeyez, e[0].get());
		auto[ey, ez] = split(eyez, e[1].get());
		auto[e0, y] = split(ey, e[0]->next()); // or e[0]->index()+1
		auto[e1, z] = split(ez, e[1]->next()); // or e[1]->index()+1
		merge(x, z);
	}

	// Make v the parent of u. Reroots u when needed
	edge_handler attach(int u, int v) {
		// (xxx u yyy, aaa v bbb)
		auto x = &nodes[v], y = &nodes[v];
		make_root(x); // (u yyy xxx, aaa v bbb)
		//  aaa v e0 u yyy xxx e1 bbb
		edge_handler e{{ptr{new node{{v, u}}}, ptr{new node{{v, u}}}}};
		auto[av, b] = split(y->root(), y->next()); // or v->index()+1
		::merge(av, e[0].get(), x, e[1].get(), b);
		return e;
	}
	int size(int u) { return (nodes[u].root()->size + 2) / 3; }
	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
};
