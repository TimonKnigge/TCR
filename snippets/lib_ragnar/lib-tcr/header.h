#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <bitset>
#include <map>
#include <algorithm>
#include <functional>

using namespace std;

typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<bool> vb;
typedef vector<vi> vvi;
typedef vector<ii> vii;
typedef vector<vii> vvii;
template<class T> 
using vv = vector<vector<T>>;

typedef long long ll;

#define REP(i,n)	for(int i = 0; i<(n); i++)
#define REPI(i,a,b)	for(int i = (a); i<(b); i++)
#define REPR(i,n)	for(int i = (n)-1; i>=0; i--)
#define REPRI(i,a,b)for(int i = (a)-1; i>=(b);i--)
#define ITER(i,v)	for(auto i : (v))
#define ITERR(i,v)	for(auto i = (v).rbegin(); i!=(v).rend(); i++)
#define F(v) (v).begin(), (v).end()
const int INF = 1000000000;
const long long LINF = 1000000000000000000ll;

// in main:
// ios_base::sync_with_stdio(false);
// cout.tie(0);

#endif 
