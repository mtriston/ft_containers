//
// Created by mtriston on 12.03.2021.
//

#ifndef FT_CONTAINERS__UTILS_HPP_
#define FT_CONTAINERS__UTILS_HPP_

#include <sstream>
#include <string>
#include <iostream>

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

template<class T>
struct greater : binary_function<T, T, bool> {
  bool operator()(const T &x, const T &y) const { return x > y; }
};

template<class T>
const T &max(const T &a, const T &b) {
  return a >= b ? a : b;
}

inline std::string to_string(int n) {
  std::stringstream ss;
  ss << n;
  std::string str = ss.str();
  return str;
}

template<class T1, class T2>
struct pair {

  typedef T1 first_type;
  typedef T2 second_type;
  first_type first;
  second_type second;

  pair() : first(), second() {}

  template<class U, class V>
  pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}

  pair(const first_type &a, const second_type &b) : first(a), second(b) {}
};

template<class T1, class T2>
ft::pair<T1, T2> make_pair(T1 x, T2 y) { return (ft::pair<T1, T2>(x, y)); }

template<class T1, class T2>
bool operator==(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class T1, class T2>
bool operator!=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(lhs == rhs);
}

template<class T1, class T2>
bool operator<(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return lhs.first < rhs.first ||
      (!(rhs.first < lhs.first) && lhs.second < rhs.second);
}

template<class T1, class T2>
bool operator<=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(rhs < lhs);
}

template<class T1, class T2>
bool operator>(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return rhs < lhs;
}

template<class T1, class T2>
bool operator>=(const pair<T1, T2> &lhs, const pair<T1, T2> &rhs) {
  return !(lhs < rhs);
}

} // namespace ft

#endif // FT_CONTAINERS__UTILS_HPP_
