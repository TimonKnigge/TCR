#include "graphs.h"

template <class T, bool directed = true>
class SmartEdgeListGraph;
template <class T>
class SmartEdgeListGraph<T,true>{
public:
	// TODO: replace _next by an iterator that is 
	// conserved on copy and move
	// since the edges are directed in this case
	// we don't have to store _u,
	// since it should be clear from the context
	// what _u is.
	
	struct E;
	typedef typename vector<E>::iterator raw_iterator;
	struct E : T {
		int _v;
		raw_iterator _next;
		E(int v, raw_iterator next, T t = T()) : T(t), _v(v), _next(next){}
		// we convert an edge to its target node
		// NOTE: when storing a weight, one must use e.c
		operator int() const {return _v;}
	};
	class iterator;
	
	typedef SmartEdgeListGraph<T,true> graph;
	typedef ::base_iterator<iterator,E> base_iterator;

	int e;
	vector<raw_iterator> _head;
	vector<E> _edges;

	// custom iterator
	class iterator : public base_iterator {
	public:
		// We keep an iterator to the
		// changing to int may have some additional optimizations
		raw_iterator it;
		const raw_iterator begin;
		// could be replaced by reference to parent container
		// so that these are still valid after a move

		// custom constructor
		iterator(raw_iterator it, raw_iterator begin) : it(it), begin(begin){}
		// copy constructors
		//iterator(iterator& i) : it(i.it), begin(i.begin){}
		//iterator(const iterator& i) : it(i.it), begin(i.begin){}

		iterator& operator++(){
			it = it->_next;
			return *this;
		}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		iterator& operator=(const iterator& r){it = r.it; return *this;}
		E& operator*(){return *it;}
		int v() const {return it->_v;}

		// container specific
		iterator reverse() const {
			return {begin + ((it-begin)^1),begin};
		}
	};

	// iterator accessors
	raw_iterator raw_end(){
		return _edges.begin() + e;
	}
	iterator begin(int _u){
		return iterator(_head[_u],_edges.begin());
	}
	iterator end(int _u=0){
		return iterator(raw_end(),_edges.begin());
	}
	struct container{
		const iterator _begin,_end; 
		iterator begin(){return _begin;}
		iterator end(){return _end;}
	};
	container edges(int _u){ return {begin(_u),end(_u)}; }

	// basic stuff
	SmartEdgeListGraph() = default;
	SmartEdgeListGraph(int V, int E) : e(E) {
		_edges.reserve(E);
		_head.assign(V,raw_end());
	}
	void set_size(int V,int E){
		e=E;
		_edges.clear();
		_edges.reserve(E);
		_head.assign(V,raw_end());
	}
	// this adds two edges at the SAME TIME
	void add_edge(int _u, int _v, T t1 = T(), T t2 = T()){
		//cerr << "adding edge "<<_u <<" to "<<_v<<"\n";
		_edges.emplace_back(_v,_head[_u],t1); _head[_u] = _edges.end()-1;
		_edges.emplace_back(_u,_head[_v],t2); _head[_v] = _edges.end()-1;
	}

	void for_each(int u, void lambda(int, T t)){
		for(auto it = begin(u); it != end(u); it++)
			lambda(it->_v, *it);
	}
};

template <class T>
class SmartEdgeListGraph<T,false>{
public:
	// TODO: replace _next by an iterator that is 
	// conserved on copy and move
	struct E;
	typedef typename vector<E>::iterator raw_iterator;
	struct E : T {
		int _u,_v;
		raw_iterator _nextu, _nextv;
		E(int u,int v, raw_iterator nextu, raw_iterator nextv, T t = T()) : T(t), _u(u), _v(v), _nextu(nextu),_nextv(nextv){}
	};
	class iterator;
	
	typedef SmartEdgeListGraph<T,false> graph;
	typedef ::base_iterator<iterator,E> base_iterator;

	vector<raw_iterator> _head;
	vector<E> _edges;
	int e;

	// custom iterator
	class iterator : public base_iterator{
	public:
		// We keep an iterator to the 
		typedef typename vector<E>::iterator raw_iterator;
		raw_iterator it;
		// could be replaced by reference to parent container
		// so that these are still valid after a move
		const int _u;
		iterator(raw_iterator it, int u) :
			it(it), _u(u){}
		iterator& operator++(){
			it = it->_u==_u ? it->_nextu : it->_nextv;
			return *this;
		}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*(){return *it;}
		int u() const {return _u;}
		int v() const {return it->_u==_u ? it->_v : it->_u;}
	};

	// iterator accessors
	raw_iterator raw_end(){ return _edges.begin()+e; }
	iterator begin(int _u){ return iterator(_head[_u],_u); }
	iterator end(int _u){ return iterator(raw_end(),_u); }
	struct container{
		const raw_iterator _begin,_end; 
		raw_iterator begin(){return _begin;}
		raw_iterator end(){return _end;}
	};
	container edges(int _u) const { return {begin(_u),end(_u)}; }

	// basic stuff
	SmartEdgeListGraph() = default;
	SmartEdgeListGraph(int V,int E) : _head(V,raw_end()), e(E){
		_edges.reserve(E);
	}
	void set_size(int V,int E){
		e=E;
		_edges.clear();
		_edges.reserve(E);
		_head.assign(V,raw_end());
	}
	void add_edge(int _u, int _v, T t1 = T(), T t2 = T()){
		_edges.emplace_back(_u,_v,_head[_u],_head[_v],t1); 
		_head[_u] = _edges.end()-1;
		_head[_v] = _edges.end()-1;
	}

	void for_each(int u, void lambda(int, T t)){
		for(auto it = begin(u); it != end(u); it++)
			lambda(it.v(), *it);
	}

	// container specific members
	// reverse an edge by applying ^1 on it.
	// but should return the iterator
};
