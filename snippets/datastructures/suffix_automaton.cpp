#include "../header.h"
using T = char; using M = map<T,int>; using V = string;
struct Node{
	int len, link; M e; bool term;		// is this a terminal node?
	Node(int len, int link=-1) : len(len), link(link), term(false) {}
};
struct SuffixAutomaton{
	const V &s; vector<Node> t; int l;	// string; tree; last added state
	SuffixAutomaton(const V &s) : s(s) { build(); }
	void build(){
		l = t.size(); t.push_back({0,-1});				// root node
		for(auto c : s){
			int p=l, x=t.size(); t.push_back({t[l].len + 1});	// new node
			while(p>=0 && t[p].e[c] == 0) t[p].e[c] = x,  p= t[p].link;
			if(p<0) t[x].link = 0;						// at root
			else {
				int q = t[p].e[c];						// the c-child of q
				if(t[q].len == t[p].len + 1) t[x].link = q;
				else {									// cloning of q
					int cl = t.size(); t.push_back(t[q]);
					t[cl].len = t[p].len + 1; t[x].link = t[q].link = cl;
					while(p >= 0 && t[p].e.count(c) > 0 && t[p].e[c] == q)
						t[p].e[c] = cl, p = t[p].link;	// relink suffix
				}
			}
			l = x;										// update last
		}
		while(l>=0) t[l].term = true, l = t[l].link;
	}
};
