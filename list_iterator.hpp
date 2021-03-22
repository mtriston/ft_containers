//
// Created by mtriston on 10.02.2021.
//

#ifndef FT_CONTAINERS__LISTITERATOR_HPP_
#define FT_CONTAINERS__LISTITERATOR_HPP_
#include "iterator.hpp"

namespace ft {

template<typename T>
struct ListNode;
//TODO: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/stl__list_8h-source.html check iterator's methods
template<typename T>
class List_iterator {
 private:
  typedef List_iterator<T> Self;
  typedef ListNode<T> Node;

  Node *_node;

 public:
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

  explicit List_iterator(Node *node = 0) : _node(node) {}
  ~List_iterator() {}
  List_iterator(List_iterator const &other) : _node(other._node) {}
  List_iterator &operator=(List_iterator const &other) {
    if (this != &other)
		_node = other._node;
	return (*this);
  }

  Node *getNode() { return _node; }

  reference operator*() const { return _node->data; }
  pointer operator->() const { return &(_node->data); }
  bool operator==(List_iterator const &rhs) { return this->_node == rhs._node; }
  bool operator!=(List_iterator const &rhs) { return this->_node != rhs._node; }

  Self operator++(int) {
	Self tmp = *this;
	this->operator++();
	return tmp;
  }

  Self &operator++() {
	_node = _node->next;
	return *this;
  }

  Self operator--(int) {
	Self tmp = *this;
	this->operator--();
	return tmp;
  }

  Self &operator--() {
	_node = _node->prev;
	return *this;
  }
};

template<typename T>
class List_const_iterator {

 private:
  typedef List_const_iterator<T> Self;
  typedef ListNode<T> Node;
  typedef List_iterator<T> iterator;

  Node *_node;

 public:
  typedef std::ptrdiff_t difference_type;
  typedef const T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

  explicit List_const_iterator(Node *node = 0) : _node(node) {}
  ~List_const_iterator() {}
  List_const_iterator(iterator const &other) : _node(other._node) {}
  List_const_iterator &operator=(List_const_iterator const &other) {
	_node(other._node);
	return (*this);
  }

  Node getNode() { return _node; }

  reference operator*() const { return _node->data; }
  pointer operator->() const { return &(_node->data); }
  bool operator==(List_const_iterator const &rhs) { return this->_node == rhs._node; }
  bool operator!=(List_const_iterator const &rhs) { return this->_node != rhs._node; }

  Self operator++(int) {
	Self tmp = *this;
	this->operator++();
	return tmp;
  }

  Self &operator++() {
	_node = _node->next;
	return *this;
  }

  Self operator--(int) {
	Self tmp = *this;
	this->operator--();
	return tmp;
  }

  Self &operator--() {
	_node = _node->prev;
	return *this;
  }
};

}
#endif //FT_CONTAINERS__LISTITERATOR_HPP_
