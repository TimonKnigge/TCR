#include "../header.h"
constexpr int ALPHABET = 26;
//using C = array<int, ALPHABET>;
using T = char;
using M = map<T,int>;
using V = string;		// could be string as well
using It = V::const_iterator;
struct Node{
	It begin, end;			// end is exclusive
	M edges;
	int parent,link;
	Node(It begin, It end, int parent) :
		begin(begin), end(end), parent(parent) ,link(-1) {}
};

struct Ukkonen{
	const V &s;
	vector<Node> nodes;
	int node, remainder;
	It cur_char;
	Ukkonen(const V &s) : s(s), nodes(1,{s.begin(),s.begin(),-1}){
		build();
	}
	void build(){
		node = 0;
		cur_char = nodes[0].end;
		remainder = 0;
		operator<<(cout);
		for(auto i = s.begin(); i != s.end(); ++i){
			Log("\n\nNEXT ITERATION\n");
			// descend from active position
			++remainder;
			while(remainder){
				Log("[node, cur_char, remainder]");
				Log(node, cur_char-s.begin(), remainder);
				Log("looking for",*i, " cur_char=",*cur_char);
				auto &n = nodes[node]; // valid till resize
				if(cur_char >= n.end){
					Log("End of current node");
					// move to or create new child
					if(n.edges.count(*i)){
						Log("Move to next node");
						// move to next node
						node = n.edges[*i];
						cur_char = nodes[node].begin;
						++cur_char;
						break;

					} else {
						Log("Create new child");
						// insert new node
						n.edges[*i]=nodes.size();
						nodes.push_back({i,s.end(),node});
						auto &n2 = nodes[node];

						// update state
						--remainder;
						if(node == 0 || n2.parent == 0){ // root?
							Log("Root; Rule 1"); // rule 1
							node = 0;
							//cur_char = i-remainder+1;
							++cur_char;
						} else {
							node = n2.edges[*i];
							cur_char = n2.begin;
						}
					}
				} else {
					// move over implicit edge or split edge
					if(*cur_char == *i){
						Log("Walk over edge");
						// just walk along
						++cur_char;
						break;
					} else {
						Log("Split edge");
						// split the edge
						// make a new node for the prefix, 
						// and update the parent pointer

						// new split node
						nodes.push_back({n.begin,cur_char,n.parent});
						// new child
						nodes.push_back({i,s.end(),int(nodes.size())-1});

						auto &n2 = nodes[node];		// new ref to the old node
						auto &nc = nodes.back();		// the new child
						auto &nn = *(nodes.end()-2);	// the split node

						// child relations
						nodes[n2.parent].edges[*nn.begin] = nodes.size()-2;
						nn.edges[*cur_char] = node;
						nn.edges[*i] = nodes.size()-1;

						// parent relations
						n2.parent = nodes.size()-2;

						// intervals
						n2.begin = cur_char;

						// update state variables
						--remainder;
						if(node == 0 || nn.parent == 0){ // root?
							Log("Root; Rule 1 in SPLIT CASE"); // rule 1
							//cur_char = i-remainder+1;
							//++cur_char;
							node = nodes[0].edges[*cur_char];
						} else {
							assert(false);
							node = n2.edges[*i];
							cur_char = n2.begin;
						}
					}
				}
				operator<<(cout);
			}
		}
	}

	ostream &operator<<(ostream &o){
		o << "String:\n";
		for(auto x : s) o << x;
		o << "\n";
		for(auto &n : nodes){
			o << "Node:\n";
			o << n.begin - s.begin() << " - " << n.end - s.begin() << "\n";
			o << n.parent << ", " << n.link << "\n";
			for(auto x : n.edges)
				o << x.first << "->" << x.second << ",\t";
			o << "\n";
		}
		o << "\n";
		return o;
	}
};

int main(){
	string s = "abcabx";
	Ukkonen st(s);
}
