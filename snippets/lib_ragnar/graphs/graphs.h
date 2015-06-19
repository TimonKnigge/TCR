#ifndef GRAPHS_H
#define GRAPHS_H
#include "header.h"
// structs to use as T type
struct Void{};
struct Capacity{int c;};
struct Weight : Capacity{int w;};
struct Int{int i;};
const bool Directed = true;
const bool Undirected = false;

// D = derived, T = object pointed to, E = edge type 
template <class D, class E>
class base_iterator : public iterator<forward_iterator_tag, E>{
public:
	virtual D& operator++() =0;
	virtual D operator++(int) {D t=static_cast<D&>(*this);++*this;return t;}
	virtual bool operator==(const D& b) const =0;
	virtual bool operator!=(const D& b) const {return !(*this==b);}
	virtual E& operator*() =0;
	E* operator->(){return &**this;}
	const E* operator->() const {return &**this;}
	virtual int u() const{return -1;};
	virtual int v() const =0;
	operator int()const{return v();} // implicit conversion to int=target node
	E& data(){return (**this);};
};
#endif
