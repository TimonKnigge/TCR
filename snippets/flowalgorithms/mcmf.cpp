#include "../header.h"
#include "./flowgraph.cpp"
#include "./dinic.cpp"
int logfloor(unsigned long long a) {
	return __builtin_clzll(1) - __builtin_clzll(a);
}
struct MinCostCirculation {
	FlowGraph &fg; int V, log_eps = 0, dt = 1;
	ll flow = 0LL, cost = 0LL;
	vi x, p, a; vector<size_t> e;
	MinCostCirculation(FlowGraph &fg)
		: fg(fg), V(fg.size()), x(V), p(V), a(V), e(V) { }
	inline ll eps() { return 1LL<<log_eps; }
	pair<ll, ll> run(int s = -1, int t = -1) {
		if (s >= 0 && t >= 0) {
			if (Dinic(fg, s, t).run())
				for (const auto &e : fg[s])
					flow += e.f;
				for (const auto &E : fg)
					for (const auto &e : E)
						if (e.f > 0)
							cost += 2LL * e.f * e.cost * V;
		} else assert(s < 0 && t < 0);
		for (const auto &E : fg) for (const auto &s : E)
			log_eps = max(log_eps, 1+logfloor(abs(V*s.cost)));
		stack<int> q; // or queue<int> q;
		for (log_eps = (dt*log_eps+dt-1)/dt; log_eps >= 0; log_eps -= dt) {
			std::fill(e.begin(), e.end(), 0);
			for (int u = 0; u < V; ++u)
				for (size_t i = 0; i < fg[u].size(); ++i)
					if (fg[u][i].cost*V + p[u] - p[fg[u][i].v] < 0LL && fg[u][i].res())
						push(u, i, fg[u][i].res());
			for (int u = 0; u < V; ++u) if (x[u] > 0) q.push(u), a[u] = 1;
			while (!q.empty()) {
				int u = q.top(); q.pop(); a[u] = 0;
				while (x[u] > 0) {
					if (e[u] == fg[u].size()) relabel(u);
					for (size_t &i = e[u]; i < fg[u].size() && x[u]; ++i) {
						auto &e = fg[u][i];
						if (e.cost*V + p[u] - p[e.v] < 0LL && fg[u][i].res()) {
							push(u, i, min(e.res(), x[u]));
							if (x[e.v] > 0 && !a[e.v]) q.push(e.v), a[e.v] = 1;
						}
					}
				}
			}
		}
		return {flow, cost /= 2LL*V};
	}
	void push(int u, size_t i, ll d) {
		auto &e = fg[u][i];
		e.f += d, x[u] -= d;
		fg[e.v][e.r].f -= d, x[e.v] += d;
		cost += 2LL * V * e.cost * d;
	}
	void relabel(int u) {
		p[u] = -LLINF;
		for (size_t i = 0; i < fg[u].size(); ++i) {
			ll pi = p[fg[u][i].v] - fg[u][i].cost*V - eps();
			if (fg[u][i].res() && p[u] < pi) p[u] = pi, e[u] = i;
		}
	}
};
