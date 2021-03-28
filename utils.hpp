//
// Created by mtriston on 12.03.2021.
//

#ifndef FT_CONTAINERS__UTILS_HPP_
#define FT_CONTAINERS__UTILS_HPP_
#include <string>
#include <sstream>

namespace ft {

template<class Arg1, class Arg2, class Result>
struct binary_function {
  typedef Arg1 first_argument_type;
  typedef Arg2 second_argument_type;
  typedef Result result_type;
};

template<class T>
struct less : binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x < y; }
};

template<class T>
struct equal_to : binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x == y; }
};

template <class T> struct greater : binary_function <T,T,bool> {
  bool operator() (const T& x, const T& y) const {return x>y;}
};

template< class T >
const T& max( const T& a, const T& b ) {
  return a >= b ? a : b;
}

inline std::string to_string(int n) {
	std::stringstream ss;
	ss << n;
	std::string str = ss.str();
	return str;
}


}

#endif //FT_CONTAINERS__UTILS_HPP_
