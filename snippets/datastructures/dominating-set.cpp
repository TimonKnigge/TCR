#include "../header.h"
struct dominating_set {
	map<ll, ll> m;
	void insert(ll a, ll b) {
		auto it = m.lower_bound(a);
		if (it != m.end() && it->second >= b)
			return;
		while (!m.empty()) {
			if ((it = m.upper_bound(a)) != m.begin()) {
				--it;
				if (it->first <= a && it->second <= b)
					m.erase(it); else break;
			} else break;
		}
		m[a] = b;
	}
};
