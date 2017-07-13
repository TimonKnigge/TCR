#include "../header.h"
#include "sequence.cpp"
struct EulerTourForest {
	struct edge {
		int u, v;
	};
	using node = seq<edge>;
	// An edge_handler is returned when creating a vertex.
	// This has to passed back in to delete the edge
	using ptr = std::unique_ptr<node>;
	struct edge_handler : array<ptr, 2> {
		edge_handler(edge_handler &&e) : array<ptr, 2>{move(e)} {
			for(auto &p : e) p.reset();
		}
		edge_handler(ptr &&l, ptr &&r) : array<ptr, 2>{{move(l), move(r)}} {}
		~edge_handler() {}
	};
	vector<node> nodes; // one node for each vertex
	EulerTourForest(int n = 0) {
		nodes.reserve(n);
		while(n--) add_vertex();
	}
	int add_vertex() {
		int v = nodes.size();
		nodes.emplace_back(edge{v, v});
		return v;
	}
	int root(int v) { return nodes[v].root()->max()->val.u; }
	node *reroot(node *x) {
		if(x == nullptr) return x;
		auto[left, right] = split(x);
		return merge(right, left);
	}
	void reroot(int v) { reroot(&nodes[v]); }
	void cut(edge_handler &&e) {
		if(e[0]->index() > e[1]->index()) swap(e[0], e[1]);
		// (xxx e0 yyy e1 zzz) -> (xxx zzz, yyy)
		auto xeyez = e[0]->root();
		auto[x, eyez] = split(e[0].get()); // xeyez
		auto[ey, ez] = split(e[1].get());  // eyez
		auto[e0, y] = split(ey, 1);        // ey
		auto[e1, z] = split(ez, 1);        // ez
		merge(x, z);
	}
	edge_handler link(int u, int v) {
		auto x = reroot(&nodes[u]), y = &nodes[v];
		auto[a, vb] = split(y); // or v->index()+1
		edge_handler e{ptr{new node{{v, u}}}, ptr{new node{{u, v}}}};
		::merge(a, e[0].get(), x, e[1].get(), vb);
		return e;
	}
	int size(int u) { return (nodes[u].root()->size_ + 2) / 3; }
	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
};
