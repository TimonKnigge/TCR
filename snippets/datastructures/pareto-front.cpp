#include "../header.h"
struct pareto_front {
	map<ll, ll> m;
	void insert(ll a, ll b) {
		auto it = m.lower_bound(a);
		if (it != m.end() && it->second >= b)
			return;
		while (!m.empty() && (it = m.upper_bound(a)) != m.begin())
			if ((--it)->first <= a && it->second <= b)
				m.erase(it); else break;
		m[a] = b;
	}
	// max { b | (a, b) \in m, a >= u }, or -LLINF otherwise.
	ll max_tail(ll u) {
		auto it = m.lower_bound(u);
		return (it != m.end() ? it->second : -LLINF);
	}
};
