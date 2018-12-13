#include "../header.h"
#include "flowgraph.h"
#include "dinic.cpp"
int logfloor(unsigned long long a) {
	return __builtin_clzll(1) - __builtin_clzll(a);
}
struct MinCostCirculation {
	FlowGraph &fg; int V, log_eps = 0, dt = 2;
	ll flow = 0LL, cost = 0LL;
	vi x, p, a; vector<vector<S>::iterator> its;
	MinCostCirculation(FlowGraph &fg)
		: fg(fg), V(fg.size()), x(V), p(V), a(V), its(V) { }
	inline ll eps() { return 1LL<<log_eps; }
	pair<ll, ll> run(int s = -1, int t = -1) {
		if (s>=0 && t>=0) Dinic(fg, s, t).run(); else assert(s<0 && t<0);
		for (const auto &E : fg) for (const auto &s : E)
			log_eps = max(log_eps, 1+logfloor(abs(V*s.cost)));
		stack<int> q; // or queue<int> q;
		for (log_eps = ((log_eps+dt-1)/dt)*dt; log_eps>=0; log_eps-=dt) {
			for (int u = 0; u < V; ++u) {
				its[u] = fg[u].begin();
				for (auto &e : fg[u])
					if (e.res() && e.cost*V + p[u] < p[e.v])
						push(u, e, e.res());
			}
			for (int u = 0; u < V; ++u) if (x[u] > 0) q.push(u), a[u] = 1;
			while (!q.empty()) {
				int u = q.top(); q.pop(); a[u] = 0;
				while (x[u] > 0) {
					if (its[u] == fg[u].end()) relabel(u);
					for (auto &i = its[u]; i != fg[u].end() && x[u]; ++i) {
						auto &e = *i;
						if (e.res() && e.cost*V + p[u] < p[e.v]) {
							push(u, e, min(e.res(), x[u]));
							if (x[e.v]>0 && !a[e.v]) q.push(e.v), a[e.v]=1;
		}	}	}	}	}
		for (const auto &e : fg[s]) flow += e.f;
 		for (const auto &E : fg) for (const auto &e : E) cost += e.f*e.cost;
		return {flow, cost /= 2LL};
	}
	void push(int u, S &e, ll d) {
		e.f += d, x[u] -= d, fg[e.v][e.r].f -= d, x[e.v] += d;
	}
	void relabel(int u) {
		ll &pu = (p[u] = -LLINF);
		for (auto it = fg[u].begin(); it != fg[u].end(); ++it) {
			auto &e = *it;
			ll pi = p[e.v] - e.cost*V;
			if (e.res() && pu < pi) pu = pi, its[u] = it;
		}
		pu -= eps();
	}
};
