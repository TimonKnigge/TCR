#include "../header.h"
template <int ALPHABET_SIZE, int (*mp)(char)>
struct AC_FSM {
	struct Node {
		int child[ALPHABET_SIZE], failure = 0;
		vector<int> match;
		Node() { for (int i = 0; i < ALPHABET_SIZE; ++i) child[i] = -1; }
	};
	vector <Node> a;
	AC_FSM() { a.push_back(Node()); }
	void construct_automaton(vector<string> &words) {
		for (int w = 0, n = 0; w < words.size(); ++w, n = 0) {
			for (int i = 0; i < words[w].size(); ++i) {
				if (a[n].child[mp(words[w][i])] == -1) {
					a[n].child[mp(words[w][i])] = a.size();
					a.push_back(Node());
				}
				n = a[n].child[mp(words[w][i])];
			}
			a[n].match.push_back(w);
		}

		queue<int> q;
		for (int k = 0; k < ALPHABET_SIZE; ++k) {
			if (a[0].child[k] == -1) a[0].child[k] = 0;
			else if (a[0].child[k] > 0) {
				a[a[0].child[k]].failure = 0;
				q.push(a[0].child[k]);
			}
		}
		while (!q.empty()) {
			int r = q.front(); q.pop();
			for (int k = 0; k < ALPHABET_SIZE; ++k) {
				if (a[r].child[k] != -1) {
					q.push(a[r].child[k]);
					int v = a[r].failure;
					while (a[v].child[k] == -1) v = a[v].failure;
					a[a[r].child[k]].failure = a[v].child[k];
					for (int w : a[a[v].child[k]].match)
						a[a[r].child[k]].match.push_back(w);
				}
			}
		}
	}

	void aho_corasick(string &sentence, vector<string> &words,vvi &matches){
		matches.assign(words.size(), vector<int>());
		int state = 0, ss = 0;
		for (int i = 0; i < sentence.length(); ++i, ss = state) {
			while (a[ss].child[mp(sentence[i])] == -1)
				ss = a[ss].failure;
			state = a[state].child[mp(sentence[i])]
			      = a[ss].child[mp(sentence[i])];
			for (int w : a[state].match)
				matches[w].push_back(i - words[w].length() + 1);
		}
	}
};
