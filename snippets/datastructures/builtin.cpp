#include "../header.h"
// Minimum Heap
#include <queue>
template<class T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

// Order Statistics Tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class TIn, class TOut>
using order_tree = tree<
	TIn, TOut, less<TIn>, // key, value types. TOut can be null_type
	rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(int r) (0-based)
// order_of_key(TIn v)
// use key pair<Tin,int> {value, counter} for multiset/multimap

// Need a much better hash function for gp_hash_table
struct custom_hash {
	static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31); }
	size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM
			= chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM); } };

template<class TIn, class TOut>
using table = gp_hash_table<TIn, TOut>;
// Or gp_hash_table<uint64_t, TOut, custom_hash>
