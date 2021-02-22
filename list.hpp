//
// Created by mtriston on 09.02.2021.
//

#ifndef FT_CONTAINERS_LIST_HPP
#define FT_CONTAINERS_LIST_HPP
#include "list_iterator.hpp"
#include "Allocator.hpp"
#include <memory>

namespace ft {

template<typename T>
struct ListNode {

  typedef T value_type;

  ListNode() : data(0), next(0), prev(0) {}
  explicit ListNode(T const &a, ListNode<T> *next = 0, ListNode<T> *prev = 0) : data(a), next(next), prev(prev) {}
  ListNode(const ListNode<T> &other) : data(other.data), next(other.next), prev(other.prev) {}
  ~ListNode() {

  }
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
  typedef ft::list_iterator<T> iterator;
  //const_iterator
  //reverse_iterator
  //const_reverse_iterator

  list() {
	allocator_ = node_allocator();
	size_ = 0;
	head_ = createNode_(0);
	tail_ = createNode_(0, head_);
	head_->next = tail_;
  }

  explicit list(size_t n, T const &val) : list() {} // fill
  // range constructor
  list(list const &x) {} // copy

  ~list() {
	erase(begin(), end());
	allocator_.destroy(tail_);
	allocator_.deallocate(tail_, 1);
	//TODO: check memory leaks
  }
  list &operator=(list const &x) { return *this; }

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(tail_); }

  iterator erase(iterator first, iterator last) {

	node_pointer first_node = first.getNode()->prev;
	node_pointer last_node = last.getNode();
	if (!first_node) {
	  first_node = createNode_(0, 0, last_node);
	  head_ = first_node;
	}
	first_node->next = last_node;
	last_node->prev = first_node;
	while (first != last) {
	  node_pointer tmp = first.getNode();
	  ++first;
	  allocator_.destroy(tmp);
	  allocator_.deallocate(tmp, 1);
	}
	return last;
  }

  bool empty() const { return head_->next == tail_; }
  size_type size() const { return ft::distance(begin(), end()); }
  //max_size

  reference front() { return head_->next->data; }
  const_reference front() const { return head_->next->data; }
  reference back() { return tail_->prev->data; }
  const_reference back() const { return tail_->prev->data; }

  void push_front(const_reference val) {

	node_pointer newNode = createNode_(val);
	newNode->next = head_->next;
	newNode->prev = head_;
	head_->next->prev = newNode;
	head_->next = newNode;
  }

  void pop_front() {

	if (!empty()) {
	  node_pointer tmp = head_->next;
	  head_->next = tmp->next;
	  tmp->next->prev = head_;
	  allocator_.destroy(tmp);
	  allocator_.deallocate(tmp, 1);
	}
  }

  void push_back(const_reference val) {

	node_pointer newNode = createNode_(val);
	newNode->prev = tail_->prev;
	newNode->next = tail_;
	tail_->prev->next = newNode;
	tail_->prev = newNode;

  }

  void pop_back() {
	if (!empty()) {
	  node_pointer tmp = tail_->prev;
	  tail_->prev = tmp->prev;
	  tmp->prev->next = tail_;
	  allocator_.destroy(tmp);
	  allocator_.deallocate(tmp, 1);
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

  node_type *head_;
  node_type *tail_;
  size_t size_;
  std::allocator<node_type> allocator_;
};

}

#endif //FT_CONTAINERS_LIST_HPP
