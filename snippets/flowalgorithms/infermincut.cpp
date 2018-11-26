#include "../header.h"
void imc_dfs(FlowGraph &fg, int u, vb &cut) {
	cut[u] = true;
	for (auto &&e : fg[u])
		if (e.cap > e.f && !cut[e.v])
			imc_dfs(fg, e.v, cut);
}
ll infer_minimum_cut(FlowGraph &fg, int s, vb &cut) {
	cut.assign(fg.size(), false);
	imc_dfs(fg, s, cut);
	ll cut_value = 0LL;
	for (size_t u = 0; u < fg.size(); ++u) {
		if (!cut[u]) continue;
		for (auto &&e : fg[u]) {
			if (cut[e.v]) continue;
			cut_value += e.cap; // {u, e.v} is in the cut
		}
	}
	return cut_value;
}
