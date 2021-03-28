//
// Created by mtriston on 22.03.2021.
//

#ifndef FT_CONTAINERS__VECTOR_HPP_
#define FT_CONTAINERS__VECTOR_HPP_
#include <stdexcept>      // std::out_of_range
#include <memory>
#include "iterator.hpp"
#include "allocator.hpp"
#include "utils.hpp"

namespace ft {

template<typename T>
class random_access_iterator {
 public:
  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::random_access_iterator_tag iterator_category;

  random_access_iterator(pointer elem = 0) : _elem(elem) {}

  random_access_iterator(random_access_iterator const &other) : _elem(other._elem) {}

  ~random_access_iterator() {}

  random_access_iterator &operator=(random_access_iterator const &other) {
	_elem = other._elem;
	return (*this);
  }
  const pointer base() const { return _elem; }

  reference operator*() const { return *_elem; }

  pointer operator->() const { return _elem; }

  bool operator==(random_access_iterator const &rhs) const { return base() == rhs.base(); }

  bool operator!=(random_access_iterator const &rhs) const { return !(*this == rhs); }

  random_access_iterator &operator++() {
	++_elem;
	return *this;
  }

  random_access_iterator operator++(int) {
	random_access_iterator old = *this;
	operator++();
	return old;
  }

  random_access_iterator &operator--() {
	--_elem;
	return *this;
  }

  random_access_iterator operator--(int) {
	random_access_iterator old = *this;
	operator--();
	return old;
  }
  random_access_iterator operator+(difference_type n) { return _elem + n; }

  random_access_iterator operator-(difference_type n) { return _elem - n; }

  difference_type operator-(random_access_iterator rhs) { return _elem - rhs._elem; }

  random_access_iterator &operator+=(difference_type n) {
	_elem += n;
	return *this;
  }
  random_access_iterator &operator-=(difference_type n) {
	_elem -= n;
	return *this;
  }

  reference operator[](std::size_t i) { return _elem[i]; }

 private:
  pointer _elem;
};

template<typename T>
bool operator==(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return lhs.base() == rhs.base();
}

template<typename T>
bool operator!=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return !(lhs == rhs);
}

template<typename T>
bool operator<(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return lhs.base() < rhs.base();
}

template<typename T>
bool operator>(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return lhs.base() > rhs.base();
}

template<typename T>
bool operator<=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return !(lhs > rhs);
}

template<typename T>
bool operator>=(random_access_iterator<T> const &lhs, random_access_iterator<T> const &rhs) {
  return !(lhs < rhs);
}

template<class T, class Alloc = ft::allocator<T> >
class vector {
 public:
  typedef T value_type;
  typedef Alloc allocator_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef random_access_iterator<T> iterator;
  typedef const random_access_iterator<T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::ptrdiff_t difference_type;
  typedef std::size_t size_type;

  explicit vector(const allocator_type &alloc = allocator_type())
	  : _start(0), _finish(0), _end_of_storage(0), _allocator(alloc) {}

  explicit vector(size_type n, const value_type &val = value_type(),
				  const allocator_type &alloc = allocator_type())
	  : _start(0), _finish(0), _end_of_storage(0), _allocator(alloc) {
	insert(n, val);
  }

  template<class InputIterator>
  vector(InputIterator first, InputIterator last,
		 const allocator_type &alloc = allocator_type())
	  : _start(0), _finish(0), _end_of_storage(0), _allocator(alloc) {
	insert(begin(), first, last);
  }

  vector(const vector &x) : _start(0), _finish(0), _end_of_storage(0), _allocator(x._allocator) {
	//TODO: finish it
  }

  /*Iterators*/
  iterator begin() { return _start; }
  const_iterator begin() const { return _start; }
  iterator end() { return _finish; }
  const_iterator end() const { return _finish; }
  reverse_iterator rbegin() { return _finish; }
  const_reverse_iterator rbegin() const { return _finish; }
  reverse_iterator rend() { return _start; }
  const_reverse_iterator rend() const { return _start; }

  /*Capacity*/
  size_type size() const { return _finish - _start; }

  size_type max_size() const { return _allocator.max_size(); }

  void resize(size_type n, value_type val = value_type()) {
	size_type old_size = size();
	if (n < size()) {
	  for (size_type i = n; i < old_size; ++i) {
		_allocator.destroy(_start + i);
	  }
	  _finish = _start + n;
	} else {
	  reserve(n);
	  for (size_type i = old_size; i < n; ++i) {
		push_back(val);
	  }
	}
  }

  size_type capacity() const { return _end_of_storage - _start; }

  bool empty() const { return _start == _finish; }

  void reserve(size_type n) {
	if (n <= size()) return;
	size_type len = _check_len(n);
	size_type save_size = size();
	pointer new_start = _allocator.allocate(len);
	for (size_type i = 0; i < save_size && save_size > 0; ++i) {
	  _allocator.construct(new_start + i, _start[i]);
	}
	delete[] _start;
	_start = new_start;
	_finish = save_size == 0 ? _start : _start + save_size;
	_end_of_storage = _start + len;
  }

  /*Element access*/
  reference operator[](size_type n) { return _start[n]; }

  const_reference operator[](size_type n) const { return _start[n]; }

  reference at(size_type n) {
	if (n > size()) {
	  throw std::out_of_range("Attempting to access beyond the bounds of an array");
	}
	return _start[n];
  }

  const_reference at(size_type n) const {
	if (n > size()) {
	  throw std::out_of_range("Attempting to access beyond the bounds of an array");
	}
	return _start[n];
  }

  reference front() { return *_start; }

  const_reference front() const { return *_start; }

  reference back() { return empty() ? *_start : _start[size() - 1]; }

  const_reference back() const { empty() ? *_start : _start[size() - 1]; }

/*Modifiers*/
//  template<class InputIterator>
//  void assign (InputIterator first, InputIterator last);

//  void assign (size_type n, const value_type& val);

  void push_back(const value_type &val) {
	insert(end(), val);
  }

  void pop_back() {
	if (!empty()) {
	  --_finish;
	  _allocator.destroy(_finish);
	}
  }

  iterator insert(iterator position, const value_type &val) {

	int pos_len = position.base() - _start;
	insert(position, 1u, val);
	return iterator(_start + pos_len);
  }

  void insert(iterator position, size_type n, const value_type &val) {
	int pos_index = position.base() - _start;
	reserve(size() + n);
	_shift_to_right(pos_index, n);
	for (int i = 0; i < n; ++i) {
	  _allocator.construct(_start + pos_index + i, val);
	}
	_finish += n;
  }

  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {
	if (first == last) return;
	size_type pos_index = position.base() - _start;
	size_type len = last - first;
	reserve(size() + len);
	_shift_to_right(pos_index, len);
	for (int i = 0; i < len; ++i) {
	  _allocator.construct(_start + pos_index + i, (*first));
	  ++first;
	}
	_finish += len;
  }

 protected:

  void _shift_to_right(size_type position, size_type length) {
	for (int i = 0; i < length; ++i) {
	  _allocator.construct(_start + size() + i, *(_start + position + i));
	}
  }

  size_type _check_len(size_type n) const {
	if (max_size() - size() < n) {
	  throw std::length_error("Trying to create an array as much as possible");
	}
	size_type len = size() + ft::max(size(), n);
	return (len > max_size()) ? max_size() : len;
  }

 private:
  pointer _start;
  pointer _finish;
  pointer _end_of_storage;
  ft::allocator<T> _allocator; // TODO: replace to allocator_type
};

}

#endif //FT_CONTAINERS__VECTOR_HPP_
