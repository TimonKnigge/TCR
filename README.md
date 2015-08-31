# Team Code Reference

A Team Code Reference for competitive programming contests. A somewhat up-to-date pdf version may be found [here](http://www.timonknigge.com/competitive-programming/source.pdf).

## TODO

#### Datastructures
- [ ] Segment Tree with lazy propagation
- [ ] Investigate advantages of Sparse Table for the RMQ (over Segment Tree)
- [x] LCA (either code or a deriviation from RMQ). ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file26), [2](https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/))
- [x] Suffix Array
- [ ] Suffix Tree ([1](web.stanford.edu/~liszt90/acm/notebook.html#file5), [2](http://acm.math.spbu.ru/~kunyavskiy/notebook/), [3](http://codeforces.com/blog/entry/16780))
- [ ] Ropes
- [ ] Implicit Cartesian Tree ([1](http://wcipeg.com/wiki/Cartesian_tree)) + investigate how to use as dynamic segment tree
- [ ] Dancing Links (+ Algo X)
- [ ] Palindromic Tree (Eertree)
- [ ] Range Update, Range Query Fenwick tree ([1](https://github.com/niklasb/tcr/blob/master/datenstrukturen/fenwick.cpp))
- [x] GCC built-in tree (documentation: [1](https://gcc.gnu.org/onlinedocs/libstdc++/manual/policy_data_structures_design.html#container.tree.interface))

#### Graphs and Trees
- [x] Articulation Points/Bridges
- [x] Biconnected Components
- [ ] Triconnected Components
- [x] Strongly Connected Components
- [x] Heavy Light Decomposition ([1](http://blog.anudeep2011.com/heavy-light-decomposition/))
- [x] Centroid Decomposition

#### Flow & Matching
- [ ] Push Relabel ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file2))
- [ ] Min Cost Max Flow
- [ ] Investigate how to adapt one of the algorithms to support minimum capacity edges
- [ ] Investigate relevancy of 'circulations' (source/sinkless flows)
- [ ] Hopcroft-Karp algorithm
- [ ] Edmond's Blossom Shrinking algorithm
- [ ] Hungarian Algorithm
- [ ] Graph Cut Inference ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file7))

#### Combinatorics, Math
- [x] 2-SAT ([1](http://codeforces.com/blog/entry/16205))
- [x] Review the code related to primes;
- [x] add fast factorization. ([1](https://www.topcoder.com/community/data-science/data-science-tutorials/prime-numbers-factorization-and-euler-function/))
- [ ] Simplex Algorithm ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file17))
- [ ] Gauss Elimination ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file14))
- [ ] Determinant Calculation
- [x] nCk % p using Lucas' Theorem
- [x] Miller Rabin

#### Geometry
- [ ] Intersecting Halfspaces ([1](http://acm.math.spbu.ru/~kunyavskiy/notebook/))
- [ ] Review 'basic' geometry code (line intersection checks etc.)
- [x] Rewrite the convex hull code

#### Misc.
- [ ] Paragraph/writeup about SQRT Decompositions
- [X] O(n lg n) Longest Increasing Subsequence ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file27))
- [ ] Game Theory: Nim & Variations, Grundy ([1](https://www.topcoder.com/community/data-science/data-science-tutorials/algorithm-games/), [2](https://github.com/niklasb/tcr/blob/master/tcr.pdf) (8.3))
- [ ] DP Optimizations: Convex Hull, Quadrangle ([1](https://github.com/niklasb/contest-algos/tree/master/convex_hull), [2](http://wcipeg.com/wiki/Convex_hull_optimization), [3](http://codeforces.com/blog/entry/8219))

#### Java    
- [X] Template    
- [X] Investigate BigNum/BigDecimal    
- [ ] Investigate `java.awt.geom` (esp. Area class) ([1](http://web.stanford.edu/~liszt90/acm/notebook.html#file10))
- [ ] Use of dates library
