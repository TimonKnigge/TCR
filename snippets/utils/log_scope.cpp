#pragma once
#include <iostream>
#include <string>
#include <tuple>

/*
void f(int a, std::string s) {
    log_scope _("f", a, s);
}
*/

struct log_scope_base {
	static void enable(bool enable = true) { log_scope_base::enabled = enable; }
	static void disable(bool disable = true) { log_scope_base::enabled = !disable; }

  protected:
	static int nesting;
	static bool enabled;
};

template <typename... Args_in>
struct log_scope : log_scope_base {
  private:
	enum class PrintType { In, Out };

  public:
	log_scope(std::string &&msg, const Args_in &... args_in)
	    : depth(log_scope_base::nesting), msg_(move(msg)), args_in_(args_in...) {
		if(!enabled()) return;
		std::cerr << spaces() << msg_ << " entered..\n";

		std::apply([&](auto &... args) { ((std::cerr << spaces() << "|> " << args << '\n'), ...); },
		           args_in_);

		++log_scope_base::nesting;
	}
	log_scope(const log_scope &) = delete;
	log_scope(log_scope &&) = delete;
	log_scope &operator=(const log_scope &) = delete;
	log_scope &operator=(log_scope &&) = delete;

	~log_scope() {
		if(!enabled()) return;
		--log_scope_base::nesting;

		if(print_on_exit_) {
			std::apply(
			    [&](auto &... args) { ((std::cerr << spaces() << "|< " << args << '\n'), ...); },
			    args_in_);
		}
		std::cerr << spaces() << msg_ << " left.\n";
	}

	// print in the middle
	template <typename... Args_Middle>
	void print(const Args_Middle &... args_middle) {
		if(!enabled()) return;
		((std::cerr << spaces() << "|- " << args_middle << '\n'), ...);
	}
	template <typename... Args_Out>
	void leave(const Args_Out &... args_out) {
		if(!enabled()) return;
		((std::cerr << spaces() << "|< " << args_out << '\n'), ...);
	}

	void exit() { print_on_exit_ = true; }

	template <typename... Args_Middle>
	void operator()(const std::string &&msg, const Args_Middle &... args_middle) {
		if(!enabled()) return;
		std::cerr << spaces() << "|" << msg;
		((std::cerr << ' ' << args_middle), ...);
		std::cerr << '\n';
	}
	template <typename... Args_Middle>
	void operator()(const Args_Middle &... args_middle) {
		if(!enabled()) return;
		std::cerr << spaces() << "|-";
		((std::cerr << ' ' << args_middle), ...);
		std::cerr << '\n';
	}

  private:
	const int depth;
	std::string spaces() { return std::string(depth, ' '); }

	const std::string msg_;
	bool print_on_exit_ = false;
	const std::tuple<const Args_in &...> args_in_;
	static bool enabled() { return log_scope_base::enabled; }
};

int log_scope_base::nesting{0};
bool log_scope_base::enabled{true};
