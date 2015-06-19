#include "../header.h"
#include "trie.h"

const int ALPHABET = 96;

class Aho_Corasick{
public:
	struct T{
		vector<int> dict; // in dictionary?
		int suffix; // the largest suffix
		int next_match; // next matching suffix
		T() : dict(0), suffix(0), next_match(-1){}
	};
	Trie<ALPHABET,T> t; 
	int count = 0;

	Aho_Corasick(){}

	void add(string s){
		t.insert(s).dict.push_back(count++);
	}

	void preprocess(){
		queue<int> q;
		REP(i,ALPHABET)
			if(t[0].child[i] > 0)
				q.push(t[0].child[i]);
			else t[0].child[i] = 0;
		while(!q.empty()){
			const int p = q.front(); q.pop();
			REP(i, ALPHABET)
				if(t[p].child[i]>0){
					auto& node = t[t[p].child[i]];
					q.push(t[p].child[i]);
					int u = t[p].suffix;
					while(t[u].child[i] < 0) u = t[u].suffix;
					u = node.suffix = t[u].child[i];
					if(t[u].dict.size() == 0)
						node.next_match =  t[u].next_match;
					else node.next_match = u;
				}
		}
	}

	vvi search(const string& s){
		int state = 0; // start in root
		int pos=0;
		vvi results(count);
		for(char c:s){ // optionally: c-='a'
			vector<int> path; // the path on which we update nodes
			while(state >= 0 && t[state].child[c] < 0)
				path.push_back(state), state = t[state].suffix;
			if(state < 0) state = 0; // root exception
			else state = t[state].child[c];
			ITER(p,path) t[p].child[c] = state;
			int match = state; // save matches
			while(match >= 0){
				ITER(patnr, t[match].dict)
					results[patnr].push_back(pos);
				match = t[match].next_match;
			}
			pos++;
		}
		return results;
	}
};
