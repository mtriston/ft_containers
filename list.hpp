//
// Created by mtriston on 09.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "allocator.hpp"
#include "iterator.hpp"
#include "utils.hpp"

namespace ft {

template<typename T>
struct ListNode;
template<typename T>
class list_iterator {
 private:
  typedef list_iterator<T> Self;
  typedef ListNode<T> Node;

  Node *_node;

 public:
  typedef std::ptrdiff_t difference_type;
  typedef T value_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

  explicit list_iterator(Node *node = 0) : _node(node) {}
  ~list_iterator() {}
  list_iterator(list_iterator const &other) : _node(other._node) {}
  list_iterator &operator=(list_iterator const &other) {
	if (this != &other)
	  _node = other._node;
	return (*this);
  }

  Node *getNode() { return _node; }

  reference operator*() const { return _node->data; }
  pointer operator->() const { return &(_node->data); }
  bool operator==(list_iterator const &rhs) const { return this->_node == rhs._node; }
  bool operator!=(list_iterator const &rhs) const { return this->_node != rhs._node; }

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
class list_const_iterator {

 private:
  typedef list_const_iterator<T> Self;
  typedef ListNode<T> Node;
  typedef list_iterator<T> iterator;

  Node *_node;

 public:
  typedef std::ptrdiff_t difference_type;
  typedef const T value_type;
  typedef const T *pointer;
  typedef const T &reference;
  typedef ft::bidirectional_iterator_tag iterator_category;

  explicit list_const_iterator(Node *node = 0) : _node(node) {}
  ~list_const_iterator() {}
  list_const_iterator(iterator const &other) : _node(other._node) {}
  list_const_iterator &operator=(list_const_iterator const &other) {
	_node(other._node);
	return (*this);
  }

  Node getNode() { return _node; }

  reference operator*() const { return _node->data; }
  pointer operator->() const { return &(_node->data); }
  bool operator==(list_const_iterator const &rhs) { return this->_node == rhs._node; }
  bool operator!=(list_const_iterator const &rhs) { return this->_node != rhs._node; }

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
struct ListNode {

  typedef T value_type;

  ListNode() : data(0), next(0), prev(0) {}

  explicit ListNode(T const &a, ListNode<T> *next = 0, ListNode<T> *prev = 0) : data(a), next(next), prev(prev) {}

  ListNode(const ListNode<T> &other) : data(other.data), next(other.next), prev(other.prev) {}

  ListNode<T> &operator=(const ListNode<T> &other) {
	if (this != &other) {
		data = other.data;
		next = other.next;
		prev = other.prev;
	}
	return *this;
  }
	~ListNode() {}

  value_type data;
  ListNode<T> *next;
  ListNode<T> *prev;

};

template<typename T, typename Allocator = ft::allocator<T> >
class list {

 public:
  typedef T value_type;
  typedef Allocator allocator_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;
  typedef ft::list_iterator<T> iterator;
  typedef ft::list_const_iterator<T> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

  explicit list(const allocator_type &alloc = allocator_type()) {
	(void)alloc;
	initBlankList_();
  }

  explicit list(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) {
	initBlankList_();
	insert(end(), n, val);
  }

  template<class InputIterator>
  list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
	initBlankList_(alloc);
	insert(end(), first, last);
  }

  list(list const &x) {
	initBlankList_();
	insert(end(), x.begin(), x.end());
  }

  ~list() {
	clear();
	deleteNode_(_root_node);
  }

  list &operator=(list const &x) {
	if (this != &x) {
	  list(x).swap(*this);
	}
	return *this;
  }

  /* Iterators */

  iterator begin() { return iterator(_root_node->next); }

  const_iterator begin() const { return const_iterator(_root_node->next); }

  iterator end() { return iterator(_root_node); }

  const_iterator end() const { return const_iterator(_root_node); }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

  /* Capacity */

  bool empty() const { return _root_node == _root_node->next; }

  size_type size() const {
	node_pointer ptr = _root_node->next;
	size_type i = 0;
	while (ptr != _root_node) {
	  ++i;
	  ptr = ptr->next;
	}
	return i;
  }

  size_type max_size() const { return allocator_.max_size(); }

  /* Element access */

  reference front() { return _root_node->next->data; }

  const_reference front() const { return _root_node->next->data; }

  reference back() { return _root_node->prev->data; }

  const_reference back() const { return _root_node->prev->data; }

  /* Modifiers */

  template<class InputIterator>
  void assign(InputIterator first, InputIterator last) {
	clear();
	insert(end(), first, last);
  }

  void assign(size_type n, const value_type &val) {
	clear();
	insert(end(), n, val);
  }

  void push_front(const_reference val) {
	insert(begin(), val);
  }

  void pop_front() {
	erase(begin());
  }

  void push_back(const_reference val) {
	insert(end(), val);
  }

  void pop_back() {
	erase(--end());
  }

  iterator insert(iterator position, const value_type &val) {
	node_pointer pos = position.getNode();
	node_pointer newNode = createNode_(val, pos->prev, pos);
	pos->prev->next = newNode;
	pos->prev = newNode;
	return iterator(newNode);
  }

  void insert(iterator position, size_type n, const value_type &val) {
	for (size_type i = 0; i < n; ++i) {
	  insert(position, val);
	}
  }

  template<class InputIterator>
  void insert(iterator position, InputIterator first, InputIterator last) {

	for (; first != last; ++first) {
	  insert(position, *first);
	}
  }

  iterator erase(iterator pos) {

	if (pos == end())
	  return (pos);
	node_pointer node = pos.getNode();
	++pos;
	node->prev->next = node->next;
	node->next->prev = node->prev;
	deleteNode_(node);
	return pos;
  }

  iterator erase(iterator first, iterator last) {

	while (first != last) {
	  iterator tmp = first++;
	  erase(tmp);
	}
	return first;
  }

  void swap(list &x) {

	node_pointer tmp_node = _root_node;
	node_allocator tmp_allocator = allocator_;

	_root_node = x._root_node;
	allocator_ = x.allocator_;

	x._root_node = tmp_node;
	x.allocator_ = tmp_allocator;
  }

  void resize(size_type n, value_type val = value_type()) {
	if (n < size()) {
	  iterator itBegin = begin();
	  ft::advance(itBegin, n);
	  erase(itBegin, end());
	} else {
	  insert(end(), n - size(), val);
	}
  }

  void clear() {
	erase(begin(), end());
  }

  /* Operations */

  void splice(iterator position, list &x) {
	splice(position, x, x.begin(), x.end());
  }

  void splice(iterator position, list &x, iterator i) {
	splice(position, x, i, ++i);
  }

  void splice(iterator position, list &x, iterator first, iterator last) {
	if (first == x.end())
	  return;

	node_pointer pos = position.getNode();
	node_pointer first_node = first.getNode();
	node_pointer last_node = last.getNode()->prev;

	x.detachNodes_(first, last);

	pos->prev->next = first_node;
	first_node->prev = pos->prev;
	pos->prev = last_node;
	last_node->next = pos;
  }

  void remove(const value_type &val) {

	iterator itBegin = begin();
	iterator itEnd = end();
	while (itBegin != itEnd) {
	  if (val == *itBegin) {
		iterator tmp = itBegin++;
		erase(tmp);
	  } else {
		++itBegin;
	  }
	}
  }

  template<class Predicate>
  void remove_if(Predicate pred) {
	iterator itBegin = begin();
	iterator itEnd = end();
	while (itBegin != itEnd) {
	  if (pred(*itBegin)) {
		iterator tmp = itBegin++;
		erase(tmp);
	  } else {
		++itBegin;
	  }
	}
  }

  template<class BinaryPredicate>
  void unique(BinaryPredicate binary_pred) {
	iterator itBegin = begin();
	iterator itEnd = end();

	while (itBegin != itEnd) {
	  iterator tmp = itBegin;
	  ++itBegin;
	  if (binary_pred(*tmp, *itBegin))
		erase(tmp);
	}
  }

  void unique() { unique(ft::equal_to<T>()); }

  void merge(list &x) { merge(x, ft::less<T>()); }

  template<class Compare>
  void merge(list &x, Compare comp) {
    if (x.empty())
	  return;
	iterator it1 = begin();
	iterator it2 = x.begin();
	iterator mergedList(this->end());
	x.detachNodes_(x.begin(), x.end());
	while (it1 != this->end() && it2 != x.end()) {
	  if (comp(*it1, *it2)) {
		insertAfter_(mergedList, it1);
		++it1;
	  } else {
		insertAfter_(mergedList, it2);
		++it2;
	  }
	  ++mergedList;
	}
	while (it1 != this->end()) {
	  insertAfter_(mergedList, it1);
	  ++it1;
	  ++mergedList;
	}
	while (it2 != x.end()) {
	  insertAfter_(mergedList, it2);
	  ++it2;
	  ++mergedList;
	}
	insertAfter_(mergedList, end());
  }

  template<class Compare>
  void sort(Compare comp) {
	_root_node->next = sortList_(_root_node->next, comp);
	node_pointer begin = _root_node->next;
	node_pointer prev;
	while (begin != _root_node) {
	  prev = begin;
	  begin = begin->next;
	}
	_root_node->prev = prev;
  }

  void sort() { sort(ft::less<T>()); }

  void reverse() {
	node_pointer prev = _root_node;
	node_pointer curr = _root_node->next;
	node_pointer next = curr->next;
	while (next != _root_node) {
	  curr->next = prev;
	  prev->prev = curr;
	  prev = curr;
	  curr = next;
	  next = curr->next;
	}
	curr->next = prev;
	prev->prev = curr;
	_root_node->next = curr;
	curr->prev = _root_node;
  }

 private:
  typedef ListNode<value_type> node_type;
  typedef typename allocator_type::template rebind<node_type>::other node_allocator;
  typedef node_type *node_pointer;

  template<class Compare>
  node_pointer sortList_(node_pointer head, Compare comp) {
	if (head == _root_node || head->next == _root_node) {
	  return head;
	}
	node_pointer second = halveList_(head);
	head = sortList_(head, comp);
	second = sortList_(second, comp);
	return mergeLists_(head, second, comp);
  }

  template<class Compare>
  node_pointer mergeLists_(node_pointer a, node_pointer b, Compare comp) {
	if (a == _root_node) return b;
	if (b == _root_node) return a;
	if (comp(a->data, b->data)) {
	  a->next = mergeLists_(a->next, b, comp);
	  a->next->prev = a;
	  a->prev = _root_node;
	  return a;
	} else {
	  b->next = mergeLists_(a, b->next, comp);
	  b->next->prev = b;
	  b->prev = _root_node;
	  return b;
	}
  }

  node_pointer halveList_(node_pointer list) {
	node_pointer first = list;
	node_pointer second = list;
	while (first->next != _root_node && second->next->next != _root_node) {
	  first = first->next->next;
	  second = second->next;
	}
	node_pointer result = second->next;
	second->next = _root_node;
	return result;
  }

  node_pointer createNode_(const_reference data, node_pointer prev = 0, node_pointer next = 0) {
	node_pointer newNode = allocator_.allocate(1);
	allocator_.construct(newNode, node_type(data));
	newNode->prev = prev;
	newNode->next = next;
	return newNode;
  }

  void deleteNode_(node_pointer node) {
	allocator_.destroy(node);
	allocator_.deallocate(node, 1);
  }

  void detachNodes_(iterator first, iterator last) {

	node_pointer first_node = first.getNode();
	node_pointer last_node = last.getNode();

	last_node->prev = first_node->prev;
	first_node->prev->next = last_node;
  }

  bool _isEqual(iterator x, iterator y) { return x == y; }

  /**
   * @brief Initialization blank list container. Needed to avoid duplication
   */
  void initBlankList_() {
	_root_node = createNode_(0);
	_root_node->next = _root_node;
	_root_node->prev = _root_node;
  }

  void insertAfter_(iterator pos, iterator val) {
	node_pointer posNode = pos.getNode();
	node_pointer valNode = val.getNode();
	posNode->next = valNode;
	valNode->prev = posNode;
  }

  node_pointer _root_node;
  node_allocator allocator_;
};

template<class T, class Alloc>
bool operator==(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  typename ft::list<T>::const_iterator lBegin = lhs.begin();
  typename ft::list<T>::const_iterator lEnd = lhs.end();
  typename ft::list<T>::const_iterator rBegin = rhs.begin();
  typename ft::list<T>::const_iterator rEnd = rhs.end();
  while (lBegin != lEnd && rBegin != rEnd) {
    if (*lBegin != *rBegin)
	  return false;
    ++lBegin;
    ++rBegin;
  }
  return (lBegin == lEnd && rBegin == rEnd);
}

template<class T, class Alloc>
bool operator!=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  return !(lhs == rhs);
}

template<class T, class Alloc>
bool operator<(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  typename ft::list<T>::const_iterator lBegin = lhs.begin();
  typename ft::list<T>::const_iterator lEnd = lhs.end();
  typename ft::list<T>::const_iterator rBegin = rhs.begin();
  typename ft::list<T>::const_iterator rEnd = rhs.end();
  while (lBegin != lEnd && rBegin != rEnd) {
    if (*lBegin < *rBegin)
      return true;
	++lBegin;
	++rBegin;
  }
  return (lBegin == lEnd && rBegin != rEnd);
}
template<class T, class Alloc>
bool operator<=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  return (lhs < rhs || lhs == rhs);
}

template<class T, class Alloc>
bool operator>(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  return !(lhs <= rhs);
}

template<class T, class Alloc>
bool operator>=(const ft::list<T, Alloc> &lhs, const ft::list<T, Alloc> &rhs) {
  return !(lhs < rhs);
}

}

#endif //FT_CONTAINERS_LIST_HPP
