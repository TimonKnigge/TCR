// Minimum Heap
#include <queue>
typedef priority_queue<T, vector<T>, greater<T>> min_queue;

// Order Statistics Tree
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<
	TIn, TOut, less<TIn>, rb_tree_tag, 
	tree_order_statistics_node_update> map_os;
// find_by_order(int r) (0-based)
// order_of_key(TIn v)
