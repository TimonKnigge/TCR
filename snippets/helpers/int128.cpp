#include "../header.h"
using lll = __int128;
ostream& operator<<( ostream& o, __int128 n ) {
	auto t = n<0 ? -n : n; char b[128], *d = end(b);
	do *--d = '0'+t%10, t /= 10; while (t);
	if(n<0) *--d = '-';
	o.rdbuf()->sputn(d,end(b)-d);
	return o;
}
