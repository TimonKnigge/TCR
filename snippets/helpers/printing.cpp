#pragma once
#include <iomanip>
#include <iostream>
#include <optional>
#include <utility>

/*
prints containers with begin/end, optional
prints + reads __int128, pair<X,Y>
*/

template <typename C>
concept bool Container = requires(C c) {
	{c.begin()};
	{c.end()};
}
|| requires(C c) {
	{std::begin(c)};
	{std::end(c)};
};

template <Container C>
    requires !std::is_same_v<C, std::string> std::ostream & operator<<(std::ostream &o,
                                                                       const C &c) {
	o << c.size() << ":";
	for(auto &x : c) o << ' ' << std::setw(2) << x;
	return o;
};

template <typename T>
std::ostream &operator<<(std::ostream &o, const std::optional<T> &v) {
	if(v)
		return o << *v;
	else
		return o << "{}";
}

std::ostream &operator<<(std::ostream &o, const __int128 &x) {
	if(x >= 1e18)
		return o << (long long)(x / (long long)1e18) << std::setw(18)
		         << (long long)((x < 0 ? -x : x) % (long long)1e18);
	else
		return o << (long long)x;
}
std::istream &operator>>(std::istream &o, __int128 &x) {
	std::string input;
	o >> input;
	if(input.size() > 18) {
		std::string high = input.substr(0, input.size() - 18);
		std::string low  = input.substr(input.size() - 18, input.size());
		__int128 highval = stoull(high);
		__int128 lowval  = stoull(low);
		x                = highval * (long long)1e18 + (highval < 0 ? -1 : 1) * lowval;
	} else {
		x = stoull(input);
	}
	return o;
}
std::ostream &operator<<(std::ostream &o, const unsigned __int128 &x) {
	if(x >= 1e18)
		return o << (long long)(x / (long long)1e18) << std::setw(18)
		         << (long long)(x % (long long)1e18);
	else
		return o << (long long)x;
}
std::istream &operator>>(std::istream &o, unsigned __int128 &x) {
	std::string input;
	o >> input;
	if(input.size() > 18) {
		std::string high = input.substr(0, input.size() - 18);
		std::string low  = input.substr(input.size() - 18, input.size());
		x = __int128(stoull(high)) * __int128((long long)1e18) + __int128(stoull(low));
	} else {
		x = stoull(input);
	}
	return o;
}

template <typename X, typename Y>
std::ostream &operator<<(std::ostream &o, const std::pair<X, Y> &p) {
	return o << '(' << p.first << ',' << p.second << ')';
}
template <typename X, typename Y>
std::istream &operator>>(std::istream &i, std::pair<X, Y> &p) {
	return i >> p.first >> p.second;
}
