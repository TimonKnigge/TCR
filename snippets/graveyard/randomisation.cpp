#include "../header.h"
#include <chrono>
using namespace chrono;
auto beg = high_resolution_clock::now();
while(high_resolution_clock::now() - beg < milliseconds(TIMELIMIT - 250)){}
