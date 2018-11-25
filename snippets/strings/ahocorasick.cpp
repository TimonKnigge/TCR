#include "../header.h"
template <int ALPHABET_SIZE, int (*mp)(char)>
struct AC_FSM {
	struct Node {
		int child[ALPHABET_SIZE], failure = 0, match_par = -1;
		vi match;
		Node() { for (int i = 0; i < ALPHABET_SIZE; ++i) child[i] = -1; }
	};
	vector<Node> a;
	vector<string> &words;
	AC_FSM(vector<string> &words) : words(words) { 
		a.push_back(Node());
		construct_automaton();
	}
	void construct_automaton() {
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
			for (int k = 0, arck; k < ALPHABET_SIZE; ++k) {
				if ((arck = a[r].child[k]) != -1) {
					q.push(arck);
					int v = a[r].failure;
					while (a[v].child[k] == -1) v = a[v].failure;
					a[arck].failure = a[v].child[k];
					a[arck].match_par = a[v].child[k];
					while (a[arck].match_par != -1
							&& a[a[arck].match_par].match.empty())
						a[arck].match_par = a[a[arck].match_par].match_par;
				}
			}
		}
	}
	void aho_corasick(string &sentence, vvi &matches){
		matches.assign(words.size(), vi());
		int state = 0, ss = 0;
		for (int i = 0; i < sentence.length(); ++i, ss = state) {
			while (a[ss].child[mp(sentence[i])] == -1)
				ss = a[ss].failure;
			state = a[state].child[mp(sentence[i])]
			      = a[ss].child[mp(sentence[i])];
			for (ss = state; ss != -1; ss = a[ss].match_par)
				for (int w : a[ss].match)
					matches[w].push_back(i + 1 - words[w].length());
		}
	}
};
