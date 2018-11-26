#include "../header.h"
#include "../datastructures/unionfind.cpp"
#include "../datastructures/skew-heap.cpp"
struct arc { int u, v; ll w; };
// Returns the weight of a minimum rooted arborescence, -1 if none exists.
ll solve(int root, int n, const vector<arc> &A) {
	UnionFind uf(n);
	vector<SkewHeap<size_t>> sk(n);
	for (size_t a = 0; a < A.size(); ++a)
		if (A[a].v != root && A[a].u != A[a].v)
			sk[A[a].v].insert(A[a].w, a);
	ll ans = 0LL; vi best(n, -LLINF);
	for (int i = 0; i < n; ++i) {
		if (uf.find(i) == root) continue;
		stack<int> st; st.push(i);
		while (true) {	
			int u = st.top(), v; ll w; size_t a;
			if (sk[u].empty()) return -1LL; // If you only want a partial
			tie(w, a) = sk[u].pop_min();	// tree just discard the stack
			v = uf.find(A[a].u);			// and carry on. DONT UNION 
			if (v == u) continue;			// `root` AFTER THE WHILE!!!
			ans += (best[u] = w);	// To reconstruct the solution: before
			if (v == root) break;	// <-this check store the arc A[a], and
			if (best[v] == -LLINF) {// at the end take any DFS tree over
				st.push(v);			// these arcs.
			} else {
				while (true) {
					sk[st.top()].adjust(-best[st.top()]);
					if (st.top() != u) sk[u].absorb(sk[st.top()]);
					if (uf.find(st.top()) == v) break;
					else uf.merge(st.top(), v), v = uf.find(v), st.pop();
				}
				swap(sk[u], sk[v]);
				st.pop(), st.push(v);
			}
		}
		while (!st.empty()) uf.merge(root, st.top()), st.pop();
		root = uf.find(root);
	}
	return ans;
}
