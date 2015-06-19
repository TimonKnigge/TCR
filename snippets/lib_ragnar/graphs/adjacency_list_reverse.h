#include "graphs.h"

template <class T=Void>
class AdjacencyListReverseGraph{
public:
	struct E : T {
		int _v;
		int _i;	// index in _edges[_v] of the reverse edge
		E(int v, int i, T t) : T(t), _v(v), _i(i) {}
		// we convert an edge to its target node
		// NOTE: when storing a weight, one must use e.c
		operator int() const {return _v;}
	};
	class iterator;

	typedef AdjacencyListReverseGraph<T> graph;
	typedef ::base_iterator<iterator,E> base_iterator;

	int V;
	vector<vector<E>> _edges;

	class iterator final : public base_iterator{
	public:
		typedef typename vector<E>::iterator raw_iterator;
		raw_iterator it;
		vector<vector<E>>& _edges;
		iterator(raw_iterator it, vector<vector<E>>& _edges):it(it),_edges(_edges){}
		iterator& operator++(){++it;return *this;}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*() override {return *it;}
		// no int u() supported
		int v() const override {return it->_v;}
		iterator reverse() const{
			return {_edges[it->_v].begin() + it->_i,_edges};
		}
	};

	iterator begin(int u) {return {_edges[u].begin(),_edges};}
	iterator end(int u) {return {_edges[u].end(),_edges};}
	struct container{
		const iterator _begin,_end;
		iterator begin(){return _begin;}
		iterator end(){return _end;}
	};
	container edges(int u) {return {begin(u),end(u)};}

	AdjacencyListReverseGraph() = default;
	AdjacencyListReverseGraph(int V):V(V),_edges(V,vector<E>()){}
	void set_size(int V){
		this->V=V;
		_edges.assign(V,vector<E>());
	}

	// we always add an edge in both directions
	void add_edge(int u, int v, T t1 = T(), T t2 = T()){
		int i1 = _edges[v].size(), i2 = _edges[u].size();
		_edges[u].push_back({v,i1,t1});
		_edges[v].push_back({u,i2,t2});
	}

	template<typename F>
	auto for_each(int u, F f) -> decltype(f(u,E(0,0,T())),void()){
		for(auto it : edges(u))
			f(it._v, it);
	}
	template<typename F>
	auto for_each(int u, F f) -> decltype(f(u),void()){
		for(auto it : edges(u))
			lambda(it._v);
	}

	// container specific functions
	int edge_count(int u){return _edges[u].size();}
};
