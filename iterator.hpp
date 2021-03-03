//
// Created by mtriston on 09.02.2021.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP
#include <cstddef> // size_t, ptrdiff_t
#include <memory> // allocator

namespace ft {

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
  typedef Iterator iterator_type;
  typedef typename iterator_traits<Iterator>::value_type value_type;
  typedef typename iterator_traits<Iterator>::difference_type difference_type;
  typedef typename iterator_traits<Iterator>::pointer pointer;
  typedef typename iterator_traits<Iterator>::reference reference;

  reverse_iterator() : current() {}
  explicit reverse_iterator(iterator_type const &other) : current(other) {}
  reverse_iterator(const reverse_iterator &other) : current(other.current) {}
  template<class It>
  reverse_iterator(const reverse_iterator<It> &other) : current(other.base()) {}

  iterator_type base() const { return current; };


};

template<typename InputIt, typename Distance>
static void do_advance(InputIt &it, Distance n, ft::random_access_iterator_tag) {
  it += n;
}

template<typename InputIt, typename Distance>
static void do_advance(InputIt &it, Distance n, ...) {
  for (Distance k = 0; k != n; ++k, ++it);
}

template<typename InputIt, typename Distance>
void advance(InputIt &it, Distance n) {
  ft::do_advance(it, n, typename ft::iterator_traits<InputIt>::iterator_category());
}

template<typename InputIt>
typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first,
																   InputIt last,
																   ft::random_access_iterator_tag) {
  return (last - first);
}

template<typename InputIt>
typename ft::iterator_traits<InputIt>::difference_type do_distance(InputIt first, InputIt last, ...) {
  size_t i = 0;
  for (; first != last; ++first, ++i);
  return i;
}

template<typename InputIt>
typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last) {
  ft::do_distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category());
}

}
#endif //FT_CONTAINERS_ITERATOR_HPP
