#include "../header.h"
template <class T>
class MaxQueue {
public:
	stack< pair<T, T> > inbox, outbox;
	void enqueue(T val) {
		T m = val;
		if (!inbox.empty()) m = max(m, inbox.top().second);
		inbox.push(pair<T, T>(val, m));
	}
	bool dequeue(T* d = nullptr) {
		if (outbox.empty() && !inbox.empty()) {
			pair<T, T> t = inbox.top(); inbox.pop();
			outbox.push(pair<T, T>(t.first, t.first));
			while (!inbox.empty()) {
				t = inbox.top(); inbox.pop();
				T m = max(t.first, outbox.top().second);
				outbox.push(pair<T, T>(t.first, m));
			}
		}
		if (outbox.empty()) return false;
		else {
			if (d != nullptr) *d = outbox.top().first;
			outbox.pop();
			return true;
		}
	}
	bool empty() { return outbox.empty() && inbox.empty(); }
	size_t size() { return outbox.size() + inbox.size(); }
	T get_max() {
		if (outbox.empty()) return inbox.top().second;
		if (inbox.empty()) return outbox.top().second;
		return max(outbox.top().second, inbox.top().second);
	}
};