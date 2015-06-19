#include "../header.h"
#include "lib/edge_list.h"
#include "union_find.cpp"
struct Weight{int w;};
using ELG = EdgeListGraph<Weight,false>;
int kruskal(ELG& g){
  g.sort([](Weight& l, Weight& r){return l.w<r.w;}); 
  int cost = 0, count = 0;
  UnionFind UF(g.V);
  ITER(e, g.edges())
    if (!UF.same(e._u, e._v)) {
      cost += e.w;
      UF.merge(e._u, e._v); 
      count++;
      if(count==g.V-1) break;
    }
  return cost;
}
