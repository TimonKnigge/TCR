#include "../header.h"
#include "./sequence_link_cut_tree.cpp"
//#include "./splay_tree.cpp"
struct empty_t {};
// provides: add_vertex, link(int,int), cut(eh), connected(int,int), size(int)
template <class T = empty_t>
struct euler_tour_forest {
	struct edge {
		int u;
		T val;
	};
	// struct node : splay_tree_node<node, edge> {
	struct node : seq<node, edge> {
		using seq<node, edge>::seq;
		virtual node *u() {
			T::merge(this->l ? &this->l->val.val : nullptr, &this->val.val,
			         this->r ? &this->r->val.val : nullptr);
			return this;
		}
		void update_to_root() {
			if(this->u()->p) this->p->update_to_root();
		}
		friend ostream &operator<<(ostream &o, const node &x) {
			o << '(';
			if(x.l)
				o << *x.l;
			else
				o << '-';
			o << x.val.u << x.val.v;
			if(x.r)
				o << *x.r;
			else
				o << '-';
			o << ")";
			return o;
		}
	};
	void update(int i) { // update all values from i to root
		nodes[i].update_to_root();
	}
	using ptr = std::unique_ptr<node>;
	struct edge_handler : pair<ptr, ptr> {
		edge_handler(edge_handler &&r) = default;
		edge_handler(ptr &&l, ptr &&r) : pair<ptr, ptr>{move(l), move(r)} {}
		edge_handler &operator=(edge_handler &&r) = delete;
		edge_handler &operator=(const edge_handler &) = delete;
		edge_handler(const edge_handler &) = delete;
	};
	vector<node> nodes; // one node for each vertex
	euler_tour_forest(int n = 0) {
		nodes.reserve(n);
		while(n--) add_vertex();
	}
	int add_vertex() {
		int v = nodes.size();
		nodes.emplace_back(edge{v});
		return v;
	}
	node *reroot(node *x) {
		if(x == nullptr) return x;
		auto lr = x->split();
		return node::merge(lr.second, lr.first);
	}
	void cut(edge_handler &&e) {
		auto x_eyez = e.first->split();          // or xey|ez
		auto yez = e.first->split(false).second; // or z
		if(e.second->root() == yez) {
			e.second->split();
			node::merge(x_eyez.first, e.second->split(false).second);
		} else {
			e.second->split(false);
			node::merge(e.second->split().first, yez);
		}
	}
	edge_handler link(int u, int v) {
		auto x = reroot(&nodes[u]), y = &nodes[v];
		auto a_vb = y->split();
		edge_handler e{ptr{new node{{v}}}, ptr{new node{{u}}}};
		node::merge(a_vb.first, e.first.get(), x, e.second.get(),
		            a_vb.second);
		return e;
	}
	bool connected(int u, int v) {
		return nodes[u].root() == nodes[v].root();
	}
	friend ostream &operator<<(ostream &o, const euler_tour_forest &t) {
		struct Comp {
			bool operator()(const node *l, const node *r) { return l < r; }
		};
		set<const node *, Comp> done;
		for(int i = 0; i < t.nodes.size(); ++i) {
			auto r = t.nodes[i].root();
			if(done.insert(r).second) o << *r << endl;
		}
		for(int i = 0; i < t.nodes.size(); ++i) {
			o << i << ": " << t.nodes[i].val.val.cur << ", "
			  << t.nodes[i].val.val.sum << endl;
		}
		return o;
	}
};
