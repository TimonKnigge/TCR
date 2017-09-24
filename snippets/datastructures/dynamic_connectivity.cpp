#include "../header.h"
#include "../utils/hash.cpp"
#include "./euler-tour-tree-edges.cpp"

struct dynamic_graph_connectivity {
	struct node_data {
		int cur, sum; // number of incident edges on current level
		int size;     // size of subtree
		node_data() : cur(0), sum(0), size(1) {}
		static void merge(const node_data *l, node_data *m,
		                  const node_data *r) {
			m->sum = m->cur, m->size = 1;
			if(l) m->sum += l->sum, m->size += l->size;
			if(r) m->sum += r->sum, m->size += r->size;
		}
	};
	using etf = euler_tour_forest<node_data>;
	struct edge_data {
		int level = -1;
		array<list<int>::iterator, 2> list_pos;
		// vector<etf::edge_handler> tree_nodes; // pointers to tree edges
		list<etf::edge_handler> tree_nodes; // pointers to tree edges
		int count = 1;                      // for duplicate edges
	};

	// the number of components
	int components;
	// The forest for each level
	vector<etf> F;
	// The adjacency lists for each level
	vector<vector<list<int>>> adj;
	// Edge data: which level and where in the adjacency lists
	struct vector_of_edges : vector<vector<edge_data>> {
		void init(int n) {
			resize(n);
			for(auto &x : *this) x.resize(n);
		}
		using vector<vector<edge_data>>::operator[];
		edge_data &operator[](const pair<int, int> &p) {
			return (*this)[p.first][p.second];
		}
		edge_data *find(pair<int, int> p) {
			auto &e = (*this)[p.first][p.second];
			return e.level >= 0 ? &e : nullptr;
		}
		edge_data &insert(const pair<int, int> &p, edge_data &&d) {
			return (*this)[p] = move(d);
		}
		void erase(const pair<int, int> &p) { (*this)[p].level = -1; }
	};
	struct small_vector_of_edges : vector<vector<edge_data>> {
		void init(int n) {
			resize(n);
			for(int i = 0; i < n; ++i) (*this)[i].resize(n - i - 1);
		}
		using vector<vector<edge_data>>::operator[];
		edge_data &operator[](const pair<int, int> &p) {
			return (*this)[p.first][p.second - p.first - 1];
		}
		edge_data *find(pair<int, int> p) {
			auto &e = (*this)[p];
			return e.level >= 0 ? &e : nullptr;
		}
		edge_data &insert(const pair<int, int> &p, edge_data &&d) {
			return (*this)[p] = move(d);
		}
		void erase(const pair<int, int> &p) { (*this)[p].level = -1; }
	};

	struct vector2d_of_edges : vector<edge_data> {
		int _n;
		void init(int n) {
			_n = n;
			resize(n * n);
		}
		using vector<edge_data>::operator[];
		edge_data &operator[](const pair<int, int> &p) {
			return (*this)[p.first * _n + p.second];
		}
		edge_data *find(pair<int, int> p) {
			auto &e = (*this)[p.first * _n + p.second];
			return e.level >= 0 ? &e : nullptr;
		}
		edge_data &insert(const pair<int, int> &p, edge_data &&d) {
			return (*this)[p] = move(d);
		}
		void erase(const pair<int, int> &p) { (*this)[p].level = -1; }
	};
	struct small_vector2d_of_edges : vector<edge_data> {
		int _n;
		void init(int n) {
			_n = n;
			resize(n * (n - 1) / 2);
		}
		using vector<edge_data>::operator[];
		int index(const pair<int, int> &p) {
			return p.first * (2 * _n - 3 - p.first) / 2 + p.second - 1;
		}
		edge_data &operator[](const pair<int, int> &p) {
			return (*this)[index(p)];
		}
		edge_data *find(pair<int, int> p) {
			auto &e = (*this)[p];
			return e.level >= 0 ? &e : nullptr;
		}
		edge_data &insert(const pair<int, int> &p, edge_data &&d) {
			return (*this)[p] = move(d);
		}
		void erase(const pair<int, int> &p) { (*this)[p].level = -1; }
	};

	using map_type = unordered_map<pair<int, int>, edge_data>;
	struct map_of_edges : map_type {
		void init(int n) {}
		edge_data &operator[](const pair<int, int> &p) {
			return this->map_type::find(p)->second;
		}
		edge_data *find(const pair<int, int> &p) {
			auto it = this->map_type::find(p);
			return it == this->end() ? nullptr : &it->second;
		}
		edge_data &insert(const pair<int, int> &p, edge_data &&d) {
			return this->map_type::emplace(p, move(d)).first->second;
		}
		void erase(const pair<int, int> &p) { this->map_type::erase(p); }
	};

	vector_of_edges edges;

	dynamic_graph_connectivity(int n) : components(n) {
		int lgn = 0;
		for(int _n = n; _n > 0; _n /= 2, ++lgn)
			;
		F.reserve(lgn);
		adj.reserve(lgn);
		lgn = 1;
		F.assign(lgn, etf(n));
		adj.resize(lgn);
		for(auto &x : adj) x.resize(n);

		edges.init(n);
	}

	bool connected(int u, int v) { return F[0].connected(u, v); }

	void update_edge_counter(int l, int u, int v, int delta) {
		F[l].nodes[u].val.val.cur += delta;
		F[l].update(u);
		F[l].nodes[v].val.val.cur += delta;
		F[l].update(v);
	}

	// push {u,v} from level l to l+1; set connect to true if this may
	// introduce a new connection
	void push_level(int l, int u, int v, bool push_tree) {
		// assert(u < v);
		// B: update edge info
		auto &edge_info = edges[{u, v}];

		// when pushing in phase B, we don't have to do
		// anything when the level is already high enough
		if(push_tree && l < edge_info.level) return;

		// add new layer if needed
		if(l + 1 >= F.size()) {
			F.push_back(etf(adj[0].size()));
			adj.push_back({});
			adj.back().resize(adj[0].size());
		}

		// assert(l == edge_info.level);
		++edge_info.level;

		// A: move to adjacency list at next level
		//    the edge_info.list_pos iterators remain valid because of
		//    splicing
		adj[l + 1][u].splice(adj[l + 1][u].end(), adj[l][u],
		                     edge_info.list_pos[0]);
		adj[l + 1][v].splice(adj[l + 1][v].end(), adj[l][v],
		                     edge_info.list_pos[1]);

		// C: add uv to the next level tree if not yet connected
		// assert(push_tree == !F[l + 1].connected(u, v));
		if(push_tree) {
			// assert(push_tree);
			// add edge to tree and store it's handlers pointers
			auto eh = F[l + 1].link(u, v);
			edge_info.tree_nodes.emplace_back(move(eh));
		}

		// D: update incidence count
		update_edge_counter(l, u, v, -1);
		update_edge_counter(l + 1, u, v, 1);
	};

	void link(int u, int v) {
		if(u > v) swap(u, v);

		if(auto it = edges.find({u, v})) {
			++it->count;
			return;
		}

		int level = 0;
		// A: adjacency list for level
		adj[level][u].push_back(v);
		auto i0 = --adj[level][u].end();
		adj[level][v].push_back(u);
		auto i1 = --adj[level][v].end();

		// B: edge data
		auto &edge_info = edges.insert({u, v}, {0, {{i0, i1}}, {}, 1});

		// C: part of tree
		if(!F[level].connected(u, v)) {
			// add edge to tree and store it's handlers pointers
			auto eh = F[level].link(u, v);
			edge_info.tree_nodes.emplace_back(move(eh));
			--components;
		}

		// D: increase incidence count
		update_edge_counter(0, u, v, 1);
	}
	void cut(int u, int v) {
		if(u > v) swap(u, v);
		// 1: Remove the current edge

		// get the edge info
		auto it = edges.find({u, v});
		auto &edge_info = *it;
		int level = edge_info.level;

		if(edge_info.count > 1) {
			--edge_info.count;
			return;
		}

		// ~D: decrease incidence count
		update_edge_counter(level, u, v, -1);

		// ~C: remove from level trees if needed
		bool intree = !edge_info.tree_nodes.empty();
		if(intree) {
			// assert(edge_info.tree_nodes.size() == level + 1);
			int l = 0;
			for(auto it = edge_info.tree_nodes.begin();
			    it != edge_info.tree_nodes.end(); ++it) {
				F[l++].cut(move(*it));
			}
			edge_info.tree_nodes.clear();
		}

		// ~A: remove from adjacency list for level (depends on B)
		adj[level][u].erase(edge_info.list_pos[0]);
		adj[level][v].erase(edge_info.list_pos[1]);

		// ~B: remove from edges
		edges.erase({u, v});

		if(!intree) return;

		// remove from level adjacency list
		// remove from trees

		// 2: Find a replacement edge. Start the search at level,
		// continue with lower levels until level 0 has been reached
		for(int l = level; l >= 0; --l) {
			// a) we sort u and v such that the component size of v is
			// smaller
			if(F[l].nodes[u].root()->val.val.size <
			   F[l].nodes[v].root()->val.val.size)
				swap(u, v);

			// b) we can afford to push all edges in T_v to the next level
			//  - for each vertex but the root in represented tree, push edge
			//  to its parent
			//  - in the ETT, only consider edge-nodes with u<v by doing
			//  in-order traversal
			auto v_root = F[l].nodes[v].root();
			auto u_root = F[l].nodes[u].root();
			{
				auto cur = v_root->min();
				auto first = cur->val.u;
				auto last = first;
				while((cur = cur->next())) {
					if(cur->val.u < last)
						push_level(l, cur->val.u, last, true);
					last = cur->val.u;
				}
				if(first < last) push_level(l, first, last, true);
			}

			// c) iterate over level i edges incident to T_v at x.
			//  - if y in T_u: add xy to F_0 .. F_level and stop
			//  - otherwise level the level of the edge

			// dfs T_v while skipping subtrees with node_data::sum == 0
			stack<etf::node *> s;
			s.push(v_root);

			while(!s.empty()) {
				auto cur = s.top();
				s.pop();

				// nothing to see here
				if(cur->val.val.sum == 0) continue;

				// succes! Start processing edges incident to this vertex
				if(cur->val.val.cur > 0) {
					// assert(cur->val.u == cur->val.v);
					// x is the current vertex in T_v
					int x = cur->val.u;
					// loop over edges on level incident to x
					// assert(cur->val.val.cur == int(adj[l][x].size()));
					// it is incremented within the loop, because we might
					// remove edges from the list
					for(auto it = adj[l][x].begin(); it != adj[l][x].end();) {
						int y = *it;
						auto y_root = F[l].nodes[y].root();
						// y in T_u?
						if(y_root == u_root) {
							// success: add (x,y) to F_l ... F_0
							for(int i = l; i >= 0; --i) {
								auto eh = F[i].link(x, y);
								auto &edge_info =
								    edges[{min(x, y), max(x, y)}];
								edge_info.tree_nodes.emplace_back(move(eh));
							}
							return;
						} else {
							// failure: push (x,y) to level l+1
							it = next(it);
							push_level(l, min(x, y), max(x, y), false);
						}
					}
				}
				// go on with children
				if(cur->l && cur->l->val.val.sum > 0) s.push(cur->l);
				if(cur->r && cur->r->val.val.sum > 0) s.push(cur->r);
			}
		}

		// no suitable replacement found
		++components;
	}
};
