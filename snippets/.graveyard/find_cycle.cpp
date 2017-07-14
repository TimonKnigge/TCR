#include "../header.h"
ii findCycle(int f(int), int x0) { // return (start, length)
  int t = f(x0), h = f(f(x0)); // find a fixpoint
  while (t != h) { t = f(t); h = f(f(h)); }
  int start = 0; h = x0; // find start-offset
  while (t != h) { t = f(t); h = f(h); start++; }
  int length = 1; h = f(t); // find period
  while (t != h) { h = f(h); length++; }
  return {start, length};
}
