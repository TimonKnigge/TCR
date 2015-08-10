#include "../header.h"
class SegmentTree{
	const static int SUM=0,MIN=1,MAX=2;
	int type;
	vi tree;
	vi data;
	int size;
	SegmentTree(int type, int N) : type(type) {
		// size = 2*2^(floor(log2 N)+1)
		size = 1 << (1 + (int)floor(log2(N)));
		tree.resize(size,-1);
	}
	void build(vi data){
		this->data=data;
		build(1,0,data.size()-1);
	}
	void build(int node, int b, int e){
		if(b==e){
			if(type == SUM) tree[node] = data[b]; // value
			else			tree[node] = b; // or index
		} else {
			int left = 2*node, right = 2*node+1;
			build(left,b,(b+e)/2);
			build(right,(b+e)/2+1,e);
			int lval = tree[left], rval = data[right];
			if(type == SUM)
				tree[node] = lval+rval;
			else{
				int lvalue = data[left], rvalue = data[right];
				if(type == MIN) tree[node] = (lvalue<=rvalue) ? lval : rval;
				else			tree[node] = (lvalue>=rvalue) ? lval : rval;
			}
		}
	}
	// query interval (b)egin to (e)nd
	int query(int i, int j){
		return query(1,0,data.size(),i,j);
	}
	int query(int node, int b, int e, int i, int j){
		if(i > e || j < b) return -1;
		if(b>=i && e <= j) return tree[node];
		int p1 = query(2*node,b,(b+e)/2,i,j);
		int p2 = query(2*node+1,(b+e)/2+1,e,i,j);
		if(p1 == -1) return p2;	// acces outside of
		if(p2 == -1) return p1; // valid range (?)
		if(type == SUM) return p1+p2;
		else if(type == MIN) return data[p1]<=data[p2] ? p1 : p2;
		else				 return data[p1]>=data[p2] ? p1 : p2;
	}
	int get(int i){return data[i];}

	int update(int node, int b, int e, int i){
		if(b==e)
			return tree[node] = data[i];
		int mid = (b+e)/2;
		if(i<=mid){
			int p1 = update(2*node,b,mid,i);
			int p2 = tree[node];
			if(type == SUM) return p1+p2;
			else if(type == MIN) return data[p1]<=data[p2] ? p1 : p2;
			else				 return data[p1]>=data[p2] ? p1 : p2;
		} else {
			int p1 = tree[node];
			int p2 = update(2*node+1,mid+1,e,i);
			if(type == SUM) return p1+p2;
			else if(type == MIN) return data[p1]<=data[p2] ? p1 : p2;
			else				 return data[p1]>=data[p2] ? p1 : p2;
		}
	}
	// Set (change) a value in `data` and update segtree
	void set(int i, int val){
		data[i]=val;
	}
	/***** LCA ******
	 * for LCA, number the nodes in the tree in DFS order
	 * then make a walk and note each node you visit
	 * do a RMQ on the part between the nodes 
	 * you want to know the LCA of
	 ****************/	
};
