// O(n lg n) time. Include rooted version.
ii dfs(int u, int par, vvi &E, vi &p) {
	p[u] = par;
	ii ret = {0, u};
	for (ll v : E[u]) if (v != par) {
		ii val = dfs(v, u, E, p);
		ret = max(ret, {val.first+1,val.second});
	}
	return ret;
}
void findcenter(vvi &E, int &c1, int &c2) {
	vi p(E.size(), -1);
	ii d1 = dfs(dfs(0, -1, E, p).second, -1, E, p);
	while (d1.first > 1) d1 = {d1.first - 2, p[d1.second]};
	c1 = d1.second;
	c2 = (d1.first == 1 ? p[d1.second] : -1);
}
bool isomorphism(vvi &E1, vvi &E2) {
	int c[2][2];
	findcenter(E1, c[0][0], c[0][1]);
	findcenter(E2, c[1][0], c[1][1]);
	if ((c[0][1] == -1) != (c[1][1] == -1))
		return false;
	if (rooted_isomorphism(c[0][0], E1, c[1][0], E2))
		return true;
	if (c[0][1] != -1 && rooted_isomorphism(c[0][1], E1, c[1][0], E2))
		return true;
	return false;
}
