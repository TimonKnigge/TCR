#include "../header.h"
using T = char;
using M = map<T,int>;		// or array<T,ALPHABET_SIZE>
using V = string;			// could be vector<T> as well
using It = V::const_iterator;
struct Node{
	int len, link; M edges; bool term;
	Node(int len, int link=-1) : len(len), link(link), term(false) {}
};
struct SuffixAutomaton{
	const string &s;
	vector<Node> t;
	int l;		// the last added state
	SuffixAutomaton(const string &s) : s(s) { build(); }
	void build(){
		// add root
		l = t.size();
		t.push_back({0,-1});
		for(auto c : s){
			print();
			int x = t.size();	// the newly added state
			t.push_back({t[l].len + 1});
			int p = l;			// loop over repeated suffixes
			while(p>=0 && t[p].edges[c] == 0)
					t[p].edges[c] = x, p = t[p].link;
			if(p<0){
				t[x].link = 0;
			} else {
				int q = t[p].edges[c];	// the c-child of q
				if(t[q].len == t[p].len + 1){
					t[x].link = q;
				} else {		// cloning of q
					int clone = t.size();
					t.push_back(t[q]);
					t[clone].len = t[p].len + 1;
					t[x].link = clone;
					t[q].link = clone;
					while(p>=0&& t[p].edges.count(c)>0 && t[p].edges[c]==q){
						t[p].edges[c] = clone;
						p = t[p].link;
					}
				}
			}
			l = x;
		}
		while(l>=0)
			t[l].term = true, l = t[l].link;
	}
	void print(){
		cout << "\nSuffix Automaton:\n";
		for(auto &n : t){
			cout << "Node: " << n.len << ", " << n.link << "\n";
			for(auto x : n.edges)
				cout << x.first << "->" << x.second << ", ";
			cout << "\n";

		}
	}
};
