
template <class T>
struct resettable_vector {
	vector<T> val, def;
	vi time; int cur = 0;
	
	resettable_vector(int n, T d) {
		val.assign(n, d); def.assign(n, d); time.assign(n, cur = 0);
	}
	
	T get(int i) { return time[i] == cur ? val[i] : def[i]; }
	void set(int i, T v) { val[i] = v; time[i] = cur; }
	void set_default(int i, T v) { def[i] = v; }
	void reset() { ++cur; }
};
