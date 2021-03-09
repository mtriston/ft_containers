//
// Created by mtriston on 09.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP

#include "List_iterator.hpp"
#include "Allocator.hpp"
#include <memory>

namespace ft {

template<typename T>
struct ListNode {

  typedef T value_type;

  ListNode() : data(0), next(0), prev(0) {}

  explicit ListNode(T const &a, ListNode<T> *next = 0, ListNode<T> *prev = 0) : data(a), next(next), prev(prev) {}

  ListNode(const ListNode<T> &other) : data(other.data), next(other.next), prev(other.prev) {}

  ~ListNode() {}

  value_type data;
  ListNode<T> *next;
  ListNode<T> *prev;

 private:
  ListNode<T> &operator=(const ListNode<T> &other) {}
};

template<typename T, typename Allocator = std::allocator<T> >
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
  typedef ft::List_iterator<T> iterator;
  typedef ft::List_const_iterator<T> const_iterator;
  //reverse_iterator
  //const_reverse_iterator

  explicit list(const allocator_type &alloc = allocator_type()) {
	initBlankList_(alloc);
  }

  explicit list(size_type n, const value_type &val = value_type(),
				const allocator_type &alloc = allocator_type()) {
	initBlankList_(alloc);
	insert(end(), n, val);
  }

  template<class InputIterator>
  list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
	initBlankList_(alloc);
	insert(end(), first, last);
  }

  list(list const &x) {
	initBlankList_(allocator_type(x.allocator_));
	insert(end(), x.begin(), x.end());
  }

  ~list() {
	clear();
	deleteNode_(last_node_);
  }

  list &operator=(list const &x) {
	if (this != &x) {
	  list(x).swap(*this);
	}
	return *this;
  }

  /* Iterators */

  iterator begin() { return iterator(last_node_->next); }

  const_iterator begin() const { return const_iterator(last_node_->next); }

  iterator end() { return iterator(last_node_); }

  const_iterator end() const { return const_iterator(last_node_); }
//  reverse_iterator rbegin();
//  const_reverse_iterator rbegin() const;
//  reverse_iterator rend();
//  const_reverse_iterator rend() const;

  /* Capacity */

  bool empty() const { return last_node_ == last_node_->next; }

  size_type size() const { return ft::distance(begin(), end()); }

  size_type max_size() const { return allocator_.max_size(); }

  /* Element access */

  reference front() { return last_node_->next->data; }

  const_reference front() const { return last_node_->next->data; }

  reference back() { return last_node_->prev->data; }

  const_reference back() const { return last_node_->prev->data; }

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

	node_pointer tmp_node = last_node_;
	allocator_type tmp_allocator = allocator_;

	last_node_ = x.last_node_;
	allocator_ = x.allocator_;

	x.last_node_ = tmp_node;
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
	  if (pred(itBegin)) {
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
	  iterator tmp = itBegin++;
	  if (binary_pred(tmp, itBegin))
		erase(tmp);
	}
  }

  void unique() { unique(_compareNodes()); }

  void merge (list& x) {
    iterator it1 = begin();
    iterator it2 = x.begin();
    node_pointer new_list = *it1 < *it2 ? it1.getNode()++ : it2.getNode()++;
    while (it1 != end() || it2 != x.end()) {
      if (*it1 < *it2) {

      }
    }

  }

 private:
  typedef ListNode<value_type> node_type;
  typedef typename std::allocator<T>::template rebind<node_type>::other node_allocator;
  typedef node_type *node_pointer;

  node_pointer createNode_(const_reference data, node_pointer prev = 0, node_pointer next = 0) {
	node_pointer newNode = allocator_.allocate(1);
	allocator_.construct(newNode, node_type(data));
	newNode->prev = prev;
	newNode->next = next;
	return newNode;
  }

  void insertNode_(iterator pos, node_pointer node) {

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

  bool _compareNodes(iterator x, iterator y) { return x == y; }

  /**
   * @brief Initialization blank list container. Needed to avoid duplication
   */
  void initBlankList_(const allocator_type &alloc = allocator_type()) {
	allocator_ = alloc;
	last_node_ = createNode_(0);
	last_node_->next = last_node_;
	last_node_->prev = last_node_;
  }

  node_pointer last_node_;
  std::allocator<node_type> allocator_;
};

}

#endif //FT_CONTAINERS_LIST_HPP
