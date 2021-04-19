//
// Created by mtriston on 12.03.2021.
//

#ifndef FT_CONTAINERS__UTILS_HPP_
#define FT_CONTAINERS__UTILS_HPP_

#include <sstream>
#include <string>
#include <iostream>
#include <cstddef>
#include <limits>
#include <new>
#include <typeinfo>
#include <memory> // allocator

namespace ft {

template<class T>
struct allocator {
  typedef T value_type;
  typedef T *pointer;
  typedef const T *const_pointer;
  typedef T &reference;
  typedef const T &const_reference;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  template<class U>
  struct rebind { typedef ft::allocator<U> other; };

  allocator() {}

  allocator(const allocator &other) {
    (void) other;
  }

  ~allocator() {}

  allocator &operator=(const allocator &other) {
    (void) other;
    return *this;
  }

  pointer address(reference x) const { return &x; }

  pointer allocate(size_type n) {
    return static_cast<pointer>(operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, std::size_t n) {
    (void) n;
    operator delete(p);
  }

  size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

  void construct(pointer p, const_reference val) { new((void *) p) T(val); }

  void destroy(pointer p) { ((T *) p)->~T(); }
};

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public ft::input_iterator_tag {};
struct bidirectional_iterator_tag : public ft::forward_iterator_tag {};
struct random_access_iterator_tag : ft::bidirectional_iterator_tag {};

template<typename Iterator>
struct iterator_traits {
  typedef typename Iterator::difference_type difference_type;
  typedef typename Iterator::value_type value_type;
  typedef typename Iterator::pointer pointer;
  typedef typename Iterator::reference reference;
  typedef typename Iterator::iterator_category iterator_category;
};

template<typename T>
struct iterator_traits<T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template<typename T>
struct iterator_traits<const T *> {
  typedef ptrdiff_t difference_type;
  typedef T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::random_access_iterator_tag iterator_category;
};

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T *, class Reference = T &>
class iterator {
 public:
  typedef T value_type;
  typedef Distance difference_type;
  typedef Pointer pointer;
  typedef Reference reference;
  typedef Category iterator_category;
};

template<typename Iterator>
class reverse_iterator : public iterator<
    typename iterator_traits<Iterator>::iterator_category,
    typename iterator_traits<Iterator>::value_type,
    typename iterator_traits<Iterator>::difference_type,
    typename iterator_traits<Iterator>::pointer,
    typename iterator_traits<Iterator>::reference> {

 protected:
  Iterator current;

 public:
  typedef reverse_iterator<Iterator> Self;
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;

  reverse_iterator() : current(Iterator()) {}

  explicit reverse_iterator(iterator_type const &other) : current(other) {}

  reverse_iterator(const reverse_iterator &other) : current(other.current) {}

  template<class It>
  reverse_iterator(const reverse_iterator<It> &other) : current(other.base()) {}

  reverse_iterator &operator=(reverse_iterator const &other) {
    if (this != &other)
      current = other.current;
    return *this;
  }

  iterator_type base() const { return current; };

  reference operator*() const {
    Iterator tmp = current;
    return *(--tmp);
  }

  pointer operator->() const { return &(operator*()); }

  bool operator==(reverse_iterator const &rhs) { return base() == rhs.base(); }

  bool operator!=(reverse_iterator const &rhs) { return !(*this == rhs); }

  Self operator++(int) {
    Self tmp = *this;
    this->operator++();
    return tmp;
  }

  Self &operator++() {
    --current;
    return *this;
  }

  Self operator--(int) {
    Self tmp = *this;
    this->operator--();
    return tmp;
  }

  Self &operator--() {
    ++current;
    return *this;
  }
};

template<typename InputIt, typename Distance>
void advance(InputIt &it, Distance n) {
  for (Distance k = 0; k != n; ++k, ++it);
}

template<typename InputIt>
typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
  size_t i = 0;
  for (; first != last; ++first, ++i);
  return i;
}

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

  pair() : first(first_type()), second(second_type()) {}

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
