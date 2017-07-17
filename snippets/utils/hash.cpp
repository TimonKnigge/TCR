#include "../header.h"
template <class T>
size_t hash_combine(size_t seed, const T &v) {
	return seed ^ (std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2));
}
namespace std {
template <typename U, typename V>
struct hash<pair<U, V>> {
	size_t operator()(const pair<U, V> &k) const {
		return hash_combine(hash_combine(0, k.first), k.second);
	}
};
}
