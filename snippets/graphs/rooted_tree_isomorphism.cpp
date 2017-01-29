// Rooted tree isomorphism in O(n lg n) time.
bool eqvec(const vi &l, const vi &r) {
	return (l.size() != r.size() ? false :
		equal(l.begin(), l.end(), r.begin()));
}
void radix_sort(vi &lv, vvi &E, vvi &ls, vi &n, vi &p) {
	sort(lv.begin(), lv.end(), [&E](const ll &l, const ll &r) {
		return E[l].size() < E[r].size(); });
	int MAXL = int(E[lv.back()].size()), MAXLABEL = 0;
	vector<set<ll>> label_level(MAXL+1, set<ll>());
	for (ll u : lv) {
		for (ll v : E[u]) if (p[u] != v) ls[u].push_back(n[v]);
		sort(ls[u].begin(), ls[u].end());
		for (size_t i = 0; i < ls[u].size(); ++i)
			label_level[i].insert(ls[u][i]),
			MAXLABEL = max(MAXLABEL, int(ls[u][i]));
	}
	vvi buckets[2] = {vvi(MAXLABEL+1, vi()), vvi(MAXLABEL+1, vi())};
	int first = int(lv.size());
	for (int len = MAXL - 1, c = 1; len >= 0; --len, c = 1 - c) {
		while (first > 0 && ls[lv[first-1]].size() > (size_t)len)
			--first, buckets[c][ls[lv[first]][len]].push_back(lv[first]);
		for (ll val : label_level[len + 1]) {
			for (ll v : buckets[1-c][val])
				buckets[c][ls[v][len]].push_back(v);
			buckets[1-c][val].clear();
		}
		label_level[len + 1].clear();
	}
	for (ll val : label_level[0]) {
		for (ll v : buckets[MAXL&1][val])
			lv[first++] = v;
		buckets[MAXL&1][val].clear();
	}
	label_level[0].clear();
}
bool rooted_isomorphism(int r1, vvi &E1, int r2, vvi &E2) {
	if (E1.size() != E2.size()) return false;
	int N = int(E1.size());
	vvi l1, l2; vi p1(N, -1LL), p2(N, -1LL), q1{r1}, q2{r2};
	while (!q1.empty() || !q2.empty()) {
		if (q1.size() != q2.size()) return false;
		l1.push_back(move(q1)); l2.push_back(move(q2));
		for (ll u : l1.back()) for (ll v : E1[u])
			if (p1[u] != v) q1.push_back(v), p1[v] = u;
		for (ll u : l2.back()) for (ll v : E2[u])
			if (p2[u] != v) q2.push_back(v), p2[v] = u;
	}
	vi n1(N, 0LL), n2(N, 0LL);
	vvi ls1(N, vi()), ls2(N, vi());
	int L = int(l1.size());
	for (int l = L - 2; l >= 0; --l) {
		radix_sort(l1[l], E1, ls1, n1, p1);
		radix_sort(l2[l], E2, ls2, n2, p2);
		if (!eqvec(ls1[l1[l][0]], ls2[l2[l][0]])) return false;
		n1[l1[l][0]] = n2[l2[l][0]] = 0;
		for (size_t i = 1; i < l1[l].size(); ++i) {
			if (!eqvec(ls1[l1[l][i]], ls2[l2[l][i]]))
				return false;
			n1[l1[l][i]] = n2[l2[l][i]] = n1[l1[l][i-1]]
				+ (eqvec(ls1[l1[l][i-1]], ls1[l1[l][i]])
					? 0 : 1);
		}
		// For the actual isomorphism: l1[l][i] can be matched with
		// l2[l][i] if their values n1,n2 are equal. Recurse from the
		// root and just assign greedily.
		// For trees where nodes contain values: take ranges where
		// li[l][j..k] are equal and sort by value just after the radix
		// sort.
	}
	return n1[r1] == n2[r2];
}
