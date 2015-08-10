#include "graphs.h"

template <class T, bool directed = false, int max_size = 100>
class AdjacencyMatrixGraph{
public:
	// types and members
	struct E : T{
		int _n;
		E() : _n(-1){}
		E(int n, T t=T()) : T(t), _n(n){}
		int& capacity(){return _n;}
		// we convert an edge to its weight
		operator int() const {return _n;}
	}; // -1 for none, 1 for present
	class iterator;

	typedef AdjacencyMatrixGraph<T,directed> graph;
	typedef ::base_iterator<iterator,E> base_iterator;

	int V;
	typedef array<E,max_size> edgerow;
	array<edgerow,max_size> _edges;

	// iterator over the edges in a row
	class iterator : public base_iterator {
	public:
		// We keep an iterator to the 
		typedef typename array<E,max_size>::iterator raw_iterator;
		using base_iterator::operator++;
		raw_iterator it;
		const raw_iterator begin, end; //needed so we don't increase past the end
		iterator(raw_iterator it,raw_iterator begin, raw_iterator end) : it(it),begin(begin), end(end){}
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*(){return *it;}
		iterator& operator++(){while(++it != end && it->_n<0){} return *this;}
		// no int u() supported
		int v() const {return it-begin;}
	};
	typedef typename iterator::raw_iterator raw_iterator;

	// iterator accessors
	iterator begin(int u) {return {_edges[u].begin(),_edges[u].begin(), _edges[u].begin()+V};}
	iterator end(int u) {return {_edges[u].begin()+V,_edges[u].begin(), _edges[u].begin()+V};}
	struct container{
		const iterator _begin,_end;
		iterator begin(){return _begin;}
		iterator end(){return _end;}
	};
	container edges(int u) const { return {_edges[u].begin(), _edges[u].begin()+V};}

	// basic stuff
	AdjacencyMatrixGraph(): V(0){
		REP(i,V) _edges[i].fill({-1,T()});
	}
	AdjacencyMatrixGraph(int V, T t = T()) : V(V){
		REP(i,V) _edges[i].fill({-1,t});
	}
	void set_size(int V, T t = T()){
		this->V=V;
		REP(i,V) _edges[i].fill({-1,t});
	}
	void add_edge(int u, int v, T t = T()){
		_edges[u][v] = {1,t};
		if(!directed)
			_edges[v][u] = {1,t};
	}

	void for_each(int u, void lambda(int, T)){
		for(auto it = begin(u); it != end(u); it++)
			lambda(it.v(), *it);
	}
	
	// container specific members
	E& edge(int u, int v){return _edges[u][v];}
	edgerow& operator[](int u){return _edges[u];}
	int& operator()(int u,int v){return _edges[u][v]._n;}
};

