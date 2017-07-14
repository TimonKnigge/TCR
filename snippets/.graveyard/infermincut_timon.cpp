#include "../header.h"
void FlowNetwork::infer_mincut_dfs(int u, vb &vs) {
	vs[u] = true;
	for (int i = h[u]; i != -1; i = e[i].nxt) {
		if (e[i].cap > e[i].flo && !vs[e[i].v])
			infer_mincut_dfs(e[i].v, vs);
	}   }

ll FlowNetwork::infer_mincut(int s) {
	vb vs(n, false);
	infer_mincut_dfs(s, vs);
	ll c = 0;
	for (int i = 0; i < e.size(); ++i) {
		if (vs[e[i ^ 1].v] && !vs[e[i].v]) {
			// The edge e[i ^ 1].v -> e[i].v,
			// given as e[i], is in the min cut.
			c += e[i].cap;
		}   }
	return c;
}
