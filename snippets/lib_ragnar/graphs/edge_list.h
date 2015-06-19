#include "graphs.h"

// we define the inner class in a separate namespace
// implementation below.
namespace inner{
	template<class E, bool directed> class template_iterator;
}

template <class T, bool directed = false>
class EdgeListGraph{
public:
	// types and members
	struct E : T{
		int _u, _v;
		E(int u, int v, T t = T()) : T(t), _u(u), _v(v) {}
		// we convert an edge to its target node
		// NOTE: when storing a weight, one must use e.c
		operator int() const {return _v;}
	};
	typedef inner::template_iterator<E,directed> iterator;
	friend iterator;
	typedef EdgeListGraph<T,directed> graph;
	typedef typename iterator::base_iterator base_iterator;
	typedef typename iterator::raw_iterator raw_iterator;

	int V;
	vector<E> _edges;

	// iterator accessors
	iterator begin(int u) { return {_edges.begin(), _edges.end(),u};}
	iterator end(int u) { return {_edges.end(), _edges.end(),u};}
	struct container{
		iterator _begin,_end; 
		iterator begin(){return _begin;}
		iterator end(){return _end();}
	};
	container edges(int _u) const { return {begin(_u),end(_u)}; }
	vector<E>& edges(){return _edges;}

	// basic stuff
	EdgeListGraph() = default;
	EdgeListGraph(int V):V(V){}
	void set_size(int V){this->V=V; _edges.clear();}
	void add_edge(int _u, int _v, T t = T()){
		// we only add it one time, even in the undirected case
		_edges.emplace_back(_u,_v,t);
	}

	void for_each(int u, void lambda(int, T)){
		for(auto it = begin(u); it != end(u); ++it)
			lambda(it.v(), *it);
	}

	// container specific members
	// iterator over all edges
	// sort the edges (invalidates iterators)
	void sort(bool comp(T& l, T&r)){
		sort(_edges.begin(), _edges.end(), comp);
	}
};

namespace inner{
	template <class E>
	class template_iterator<E,false> : public ::base_iterator<template_iterator<E,false>,E>{
	public:
		typedef typename vector<E>::iterator raw_iterator;
		typedef typename template_iterator<E,false>::template_iterator<E,false> iterator;
		typedef typename ::base_iterator<iterator,E> base_iterator;

		// data members
		raw_iterator it;
		const int _u; // the node we iterate
		const raw_iterator end; //needed so we don't increase past the end
		template_iterator(raw_iterator begin, raw_iterator end, int u):it(begin),_u(u),end(end){
			// iterate from begin to the first edge from _u
			while(it != end && _u!=it->_u && _u!= it->_v){++it;}
		}
		iterator& operator++(){
			while(++it != end && _u!=it->_u && _u!= it->_v){} return *this;
		}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*(){return *it;}
		int u() const {return _u;}
		int v() const {return _u == it->_u ? it->_v : it->_u;}
	};

	template <class E>
	class template_iterator<E,true> : public ::base_iterator<template_iterator<E,true>,E>{
	public:
		typedef typename template_iterator<E,true>::template_iterator<E,true> iterator;
		typedef typename ::base_iterator<iterator,E> base_iterator;
		typedef typename vector<E>::iterator raw_iterator;

		// data members
		raw_iterator it;
		const raw_iterator end; //needed so we don't increase past the end

		// constructor
		template_iterator(raw_iterator begin, raw_iterator end, int _u):it(begin),end(end){
			// iterate from begin to the first edge from _u
			while(it != end && _u!=it->_u){++it;};
		}

		// functions
		iterator& operator++(){
			int _u = it->_u;
			// increment at least once
			while(++it != end && _u!=it->_u){} return *this;
		}
		using base_iterator::operator++;
		bool operator==(const iterator& b) const {return it==b.it;}
		E& operator*(){return *it;}
		int u() const {return it->_u;}
		int v() const {return it->_v;}
	};
}
