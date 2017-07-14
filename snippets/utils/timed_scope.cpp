#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <optional>
#include <string>

/*
timed_scope _("this scope");
timed_scope _([](auto mus){ cout << "scope took " << mus << "µs"; });
timed_scope _(timed_scope::duration&);	// increments duration on exit
*/

// triggers callback with duration when leaving scope
struct timed_scope {
	using clock         = std::chrono::high_resolution_clock;
	using time_point    = clock::time_point;
	using duration_base = clock::duration;
	using rep           = std::chrono::microseconds::rep;

	// add destructor
	struct duration : duration_base {
		std::string msg_;
		duration(const std::string &msg) : duration_base(), msg_(msg) {}
		duration()                 = default;
		duration(const duration &) = delete;
		duration(duration &&)      = delete;
		~duration() {
			using namespace std::chrono;
			if(!msg_.empty()) std::cout << msg_ << ": ";
			std::cout << duration_cast<microseconds>(*this).count() << " µs\n";
		}
	};

	timed_scope(const std::function<void(rep)> &f) : f_(f), msg_(), start_(clock::now()) {}
	timed_scope(const std::string &msg) : f_(nullptr), msg_(msg), start_(clock::now()) {}
	timed_scope(duration_base &d) : d_(&d), start_(clock::now()) {}
	timed_scope(const timed_scope &) = delete;
	timed_scope(timed_scope &&)      = delete;
	timed_scope &operator=(const timed_scope &) = delete;
	timed_scope &operator=(timed_scope &&) = delete;

	~timed_scope() {
		using namespace std::chrono;
		auto end               = clock::now();
		auto duration          = end - start_;
		auto millisecond_count = duration_cast<microseconds>(duration).count();
		if(f_) f_(millisecond_count);
		if(!msg_.empty()) std::cout << msg_ << " took " << millisecond_count << "µs" << '\n';
		if(d_) *d_ += duration;
	}

  private:
	std::function<void(rep)> f_;
	std::string msg_;
	duration_base *d_;
	time_point start_;
};
