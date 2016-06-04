// O(n^2) preprocessing, O(n lg n) nearest point queries with O(1) expected distance function evaluations
template<class T, class D, D(*op)(const T&, const T&)>
struct aesa {
	vector<T> &pt;
	vector<vector<D>> d;
	aesa(vector<T> &p) : pt(p), d(p.size(), vector<D>(p.size(), D(0))) {
		for (size_t i = 0; i < p.size(); ++i)
			for (size_t j = 0; j < p.size(); ++j)
				d[i][j] = op(p[i], p[j]);
	}
	size_t nearest(const T &target) {
		priority_queue<pair<ii, size_t>, vector<pair<ii, size_t>>, greater<pair<ii, size_t>>> pq;
		for (size_t i = 0; i < pt.size(); ++i)
			pq.push({{0LL, 0LL}, i});
		size_t best = 0;
		D bestdist = D(-1);
		for (ll round = 1; pq.size() > 0; ++round) {
			size_t cand = pq.top().second;
			ll canddist = op(target, pt[cand]);
			if (bestdist == D(-1) || canddist < bestdist)
				best = cand, bestdist = canddist;
			while (!pq.empty() && pq.top().first.first < round) {
				size_t i = pq.top().second; pq.pop();
				ll lb = abs(canddist - d[cand][i]);
				if (lb < bestdist)
					pq.push({{round, lb}, i});
			}
		}
		return best;
	}
};

