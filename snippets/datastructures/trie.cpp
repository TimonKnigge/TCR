#include "../header.h"
const int ALPHABET_SIZE = 26;
inline int mp(char c) { return c - 'a'; }

struct Node {
	Node* ch[ALPHABET_SIZE];
	bool isleaf = false;
	Node() {
		for(int i = 0; i < ALPHABET_SIZE; ++i) ch[i] = nullptr;
	}

	void insert(string &s, int i = 0) {
		if (i == s.length()) isleaf = true;
		else {
			int v = mp(s[i]);
			if (ch[v] == nullptr)
				ch[v] = new Node();
			ch[v]->insert(s, i + 1);
		}
	}

	bool contains(string &s, int i = 0) {
		if (i == s.length()) return isleaf;
		else {
			int v = mp(s[i]);
			if (ch[v] == nullptr) return false;
			else return ch[v]->contains(s, i + 1);
		}
	}

	void cleanup() {
		for (int i = 0; i < ALPHABET_SIZE; ++i)
			if (ch[i] != nullptr) {
				ch[i]->cleanup();
				delete ch[i];
			}
	}
};