#include "../header.h"
struct Void{};
template <int ALPHABET = 26, class T = Void>
struct Trie{
	struct Node : T{
		bool leaf;
		array<int,ALPHABET> child;
		int parent; char c;
		Node():leaf(false),parent(-1){child.fill(-1);}
		Node(int c, int p) : leaf(false),parent(p), c(c){
			child.fill(-1);
		}
		int &operator[](int i){return child[i];}
	};

	vector<Node> data;

	const static int root = 0;

	int n; // # elements added, current node

	Trie() : n(0){
		data.push_back(Node());
	} // and init vector

	Node &insert(string::iterator it, const string::iterator end){
		int n = root;
		for(;it!=end;it++){
			char c = *it; // add -'a' for normal chars
			int &next = data[n][c];
			if(next>=0) n = next;
			// if using vector, use push_back
			else
				data.push_back(Node(c,n)),n=data[n][c]=data.size()-1;
		} // (^) create a node at index size
		data[n].leaf= true;
		return data[n];
	}

	Node &insert(string s){return insert(s.begin(), s.end());}

	Node &operator[](int n){return data[n];}

	int find(const string &s){
		n = root;
		for(auto &&c : s){
			n = data[n][c]; // add -'a' for normal chars
			if(n<0) return -1;
		}
		return n;
	}

};
