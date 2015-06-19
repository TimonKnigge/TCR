#include "../header.h"

// return (start, length)
ii findCycle(int f(int), int x0) {
  // find a fixpoint
  int tortoise = f(x0), hare = f(f(x0));
  while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
  // find start-offset
  int start = 0; hare = x0;
  while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); start++; }
  // find period
  int length = 1; hare = f(tortoise);
  while (tortoise != hare) { hare = f(hare); length++; }
  return {start, length};
}
