#include "../header.h"
struct edge {
	int v;
	list<edge>::iterator rev;
	edge(int _v) : v(_v) {};
};
void add_edge(vector< list<edge> > &adj, int u, int v) {
	adj[u].push_front(edge(v));
	adj[v].push_front(edge(u));
	adj[u].begin()->rev = adj[v].begin();
	adj[v].begin()->rev = adj[u].begin();
}
void remove_edge(vector< list<edge> > &adj, int s, list<edge>::iterator e) {
	adj[e->v].erase(e->rev);
	adj[s].erase(e);
}
eulerian_circuit(vector< list<edge> > &adj, vi &c, int start = 0) {
	stack<int> st;
	st.push(start);
	while(!st.empty()) {
		int u = st.top().first;
		if (adj[u].empty()) {
			c.push_back(u);
			st.pop();
		} else {
			st.push(adj[u].front().v);
			remove_edge(adj, u, adj[u].begin());
		}
	}
}
