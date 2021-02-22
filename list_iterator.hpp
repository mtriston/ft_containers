//
// Created by mtriston on 10.02.2021.
//

#ifndef FT_CONTAINERS__LISTITERATOR_HPP_
#define FT_CONTAINERS__LISTITERATOR_HPP_
#include "iterator.hpp"

namespace ft {

template<typename T> struct ListNode;
//TODO: https://gcc.gnu.org/onlinedocs/libstdc++/libstdc++-html-USERS-4.2/stl__list_8h-source.html check iterator's methods
template<typename T>
 class list_iterator : public ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> > {

 public:
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> >::difference_type difference_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> >::value_type value_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> >::pointer pointer;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> >::reference reference;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, ft::ListNode<T> >::iterator_category iterator_category;

  explicit list_iterator(pointer ptr = 0) : ptr_(ptr) {}
  ~list_iterator() {}
  list_iterator(list_iterator const &other) : ptr_(other.ptr_) {}
  list_iterator &operator=(list_iterator const &other) {
	ptr_(other.ptr_);
	return (*this);
  }

   pointer getNode() { return ptr_; }

   T &operator*() { return ptr_->data; }
  T *operator->() { return &(ptr_->data); }
  bool operator==(list_iterator const &rhs) { return this->ptr_ == rhs.ptr_; }
  bool operator!=(list_iterator const &rhs) { return this->ptr_ != rhs.ptr_; }

  list_iterator operator++(int) {
	list_iterator tmp = *this;
	this->operator++();
	return tmp;
  }

  list_iterator &operator++() {
	ptr_ = ptr_->next;
	return *this;
  }

  list_iterator operator--(int) {
	list_iterator tmp = *this;
	this->operator--();
	return tmp;
  }

  list_iterator &operator--() {
	ptr_ = ptr_->prev;
	return *this;
  }

  private:
   pointer ptr_;
};

}
#endif //FT_CONTAINERS__LISTITERATOR_HPP_
