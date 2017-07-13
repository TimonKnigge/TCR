#include "../header.h"
#include "sequence.cpp"

struct EulerTourForest {
	struct T {
		int u, v; // edge from u to v
	};
	using node = seq<T>;
	// An edge_handler is returned when creating a vertex.
	// This has to passed back in to delete the edge
	using edge_handler = array<node *, 2>;
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
	void make_root(int v) {
		// xxx v yyy -> v yyy xxx
		node *x = &nodes[v];
		if(x->p == nullptr) return;
		auto[left, right] = split(x->root(), x); // left: xxx, right: v yyy
		merge(right, left);
	}

	// Cut from parent (if exists).
	void cut(const edge_handler &e) {
		// xxx e1 yyy e2 zzz -> (xxx zzz, yyy)
		// cut e1:
		auto xeyez = e[0]->root();
		auto[x, eyez] = split(xeyez, e[0]);
		auto[ey, ez] = split(eyez, e[1]);
		auto[e1, y] = split(ey, e[0]->next()); // or e[0]->index()+1
		auto[e2, z] = split(ez, e[1]->next()); // or e[1]->index()+1
		delete e1;
		delete e2;
		merge(x, z);
	}

	// Join u and v
	void attach(int u, int v) {

		seq<T> *vroot = nodes[2 * v].root(), *i1, *i2;
		int end = nodes[2 * v + 1].index();
		tie(i1, i2) = split(vroot, end);
		merge(i1, merge(nodes[2 * u].root(), i2));
	}
	int size(int u) { return (nodes[2 * u].root()->size + 2) / 3; }
};
