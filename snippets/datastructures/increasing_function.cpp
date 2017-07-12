#include <map>
#include <optional>

template <typename T>
struct increasing_function {
	std::map<T, T> m;

	void set(T x, T y) {
		auto next = m.upper_bound(x);
		if(next == m.begin() || prev(next)->second < x) {
			while(next != m.end() && next->second <= y) next = m.erase(next);
			m.insert(next, {x, y});
		}
	}
	std::optional<T> get(T x) {
		auto next = m.upper_bound(x);
		if(next == m.begin()) return {};
		return prev(next)->second;
	}
};
