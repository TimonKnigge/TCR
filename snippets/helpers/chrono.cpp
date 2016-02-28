#include "../header.h" // auto in type signature does not work on CF.
auto now(){ return chrono::high_resolution_clock::now(); }
using TP = decltype(now());	// time point
auto duration(TP t1, TP t2){
	return chrono::duration_cast<chrono::microseconds>(t2-t1).count();
}
