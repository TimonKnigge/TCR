#include <chrono>

auto beg = chrono::high_resolution_clock::now();
while (true) {
	auto en = chrono::high_resolution_clock::now();
	if (chrono::duration_cast<chrono::milliseconds>(en-beg).count()
		> TIMELIMIT - 250) break;
	// randomize
}

