//
// Created by mtriston on 10.02.2021.
//

#ifndef FT_CONTAINERS__LISTITERATOR_HPP_
#define FT_CONTAINERS__LISTITERATOR_HPP_
#include "iterator.hpp"

template<typename T>
class list_iterator : public ft::iterator<ft::bidirectional_iterator_tag, T> {

 public:
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
  typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;

  explicit list_iterator(ft::ListNode<T> ptr = 0) : ptr_(ptr) {}
  ~list_iterator() {}
  list_iterator(list_iterator<T> const &other) : ptr_(other.ptr_) {}
  list_iterator<T> &operator=(list_iterator<T> const &other) {
	ptr_(other.ptr_);
	return (*this);
  }
  T &operator*() { return ptr_->data; }
  T *operator->() { return &(ptr_->data); }
  bool operator==(iterator const &rhs) { return this->ptr_ == rhs.ptr_; }
  bool operator!=(iterator const &rhs) { return this->ptr_ != rhs.ptr_; }
  iterator operator++(int) {
	iterator tmp = *this;
	ptr_ = ptr_->next;
	return tmp;
  }
  iterator &operator++() {
	ptr_ = ptr_->next;
	return *this;
  }
  iterator operator--(int) {
	iterator tmp = *this;
	ptr_ = ptr_->prev;
	return tmp;
  }
  iterator &operator--() {
	ptr_ = ptr_->prev;
	return *this;
  }

 private:
  pointer ptr_;

};

#endif //FT_CONTAINERS__LISTITERATOR_HPP_
