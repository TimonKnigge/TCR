#include "../header.h"
using T = char;
using M = map<T,int>;		// or array<T,ALPHABET_SIZE>
using V = string;			// could be vector<T> as well
using It = V::const_iterator;
struct Node{
	It b, e; M edges; int link;		// end is exclusive
	Node(It b, It e) : b(b), e(e), link(-1) {}
	int size() const { return e-b; }
};
struct SuffixTree{
	const V &s; vector<Node> t;
	int root,n,len,remainder,llink; It edge;
	SuffixTree(const V &s) : s(s) { build(); }
	int add_node(It b, It e){ return t.push_back({b,e}), t.size()-1; }
	int add_node(It b){ return add_node(b,s.end()); }
	void link(int node){ if(llink) t[llink].link = node; llink = node; }
	void build(){
		len = remainder =  0; edge = s.begin();
		n = root = add_node(s.begin(), s.begin());
		for(auto i = s.begin(); i != s.end(); ++i){
			++remainder; llink = 0;
			while(remainder){
				if(len == 0) edge = i;
				if(t[n].edges[*edge] == 0){			// add new leaf
					t[n].edges[*edge] = add_node(i); link(n);
				} else {
					auto x = t[n].edges[*edge];		// neXt node [with edge]
					if(len >= t[x].size()){			// walk to next node
						len -= t[x].size(); edge += t[x].size(); n = x;
						continue;
					}
					if(*(t[x].b + len) == *i){		// walk along edge
						++len; link(n); break;
					}								// split edge
					auto split = add_node(t[x].b, t[x].b+len);
					t[n].edges[*edge] = split;
					t[x].b += len;
					t[split].edges[*i] = add_node(i);
					t[split].edges[*t[x].b] = x;
					link(split);
				}
				--remainder;
				if(n == root && len > 0)
					--len, edge = i - remainder + 1;
				else n = t[n].link > 0 ? t[n].link : root;
			}
		}
	}
};
