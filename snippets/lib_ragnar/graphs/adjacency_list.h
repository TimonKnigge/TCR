#include "graphs.h"

template <class T=Void, bool directed = Directed>
class AdjacencyListGraph{
public:
	struct E : T {
		int _v;
		E(int v, T t) : T(t), _v(v) {}
		// we convert an edge to its target node
		// NOTE: when storing a weight, one must use e.c
		operator int() const {return _v;}
	};
	class iterator;

	typedef AdjacencyListGraph<T,directed> graph;
	typedef ::base_iterator<iterator,E> base_iterator;

	int V;
	vector<vector<E>> _edges;

	class iterator final : public base_iterator{
	public:
		typedef typename vector<E>::iterator raw_iterator;
		raw_iterator it;
		iterator(raw_iterator it):it(it){}
		iterator& operator++(){++it;return *this;}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*() override {return *it;}
		// no int u() supported
		int v() const override {return it->_v;}
	};

	iterator begin(int u) {return _edges[u].begin();}
	iterator end(int u) {return _edges[u].end();}
	struct container{
		const iterator _begin,_end;
		iterator begin(){return _begin;}
		iterator end(){return _end;}
	};
	container edges(int u) {return {begin(u),end(u)};}

	AdjacencyListGraph() = default;
	AdjacencyListGraph(int V):V(V),_edges(V,vector<E>()){}
	void set_size(int V){
		this->V=V;
		_edges.assign(V,vector<E>());
	}

	void add_edge(int u, int v, T t = T()){
		_edges[u].push_back({v,t});
		if(!directed)
			_edges[v].push_back({u,t});
	}

	template<typename F>
	auto for_each(int u, F f) -> decltype(f(u,E(0,T())),void()){
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

