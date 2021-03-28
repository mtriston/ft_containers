//
// Created by mtriston on 19.02.2021.
//

#ifndef FT_CONTAINERS__ALLOCATOR_HPP_
#define FT_CONTAINERS__ALLOCATOR_HPP_
#include <cstddef>
#include <limits>
#include <new>

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
  template< class U > struct rebind { typedef ft::allocator<U> other; };

  allocator() {}
  allocator(const allocator &other) {
	(void)other;
  }
  ~allocator() {}

  allocator &operator=(const allocator &other) {
	(void)other;
	return *this;
  }

  pointer address(reference x) const { return &x; }

  pointer allocate(size_type n) {
	return static_cast<pointer>(operator new(n * sizeof(value_type)));
  }

  void deallocate(pointer p, std::size_t n) {
	  (void)n;
  	operator delete(p);
	}

  size_type max_size() const { return std::numeric_limits<size_type>::max() / sizeof(value_type); }

  void construct(pointer p, const_reference val) { new((void *) p) T(val); }

  void destroy(pointer p) { ((T *) p)->~T(); }
};

}

#endif //FT_CONTAINERS__ALLOCATOR_HPP_
