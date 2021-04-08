//
// Created by mtriston on 29.03.2021.
//

#include <map>

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#include "allocator.hpp"
#include "utils.hpp"

namespace ft {

enum Color {
  RED,
  BLACK,
};

template<class T>
struct treeNode {
  typedef T value_type;

  Color color;
  treeNode *parent;
  treeNode *left;
  treeNode *right;
  value_type data;

  treeNode(const value_type &val = value_type()) : data(val) {}
};

template<class T, class Compare>
struct map_iterator {

  typedef T value_type;
  typedef std::ptrdiff_t difference_type;
  typedef T *pointer;
  typedef T &reference;
  typedef ft::bidirectional_iterator_tag iterator_category;
  typedef map_iterator<T, Compare> _Self;
  typedef treeNode<T> _Node;

  map_iterator(_Node *node, _Node *last_node) {
    _node = node;
    _end = last_node;
  }

  map_iterator(_Self const &x) {
    _node = x._node;
    _end = x._end;
  }

  ~map_iterator() {}

  _Self &operator=(_Self const &x) {
    if (this != &x) {
      _node = x._node;
      _node = x._end;
    }
    return *this;
  }

  bool operator==(_Self const &rhs) const { return _node == rhs._node; }

  bool operator!=(_Self const &rhs) const { return !(*this == rhs); }

  reference operator*() const { return _node->data; }

  pointer operator->() const { return &operator*(); }

  _Self &operator++() {

    if (_node->right != _end) {
      _node = _node->right;
      while (_node->left != _end) {
        _node = _node->left;
      }
    } else {
      _Node *current = _node->parent;
      while (_node == current->right) {
        _node = current;
        current = current->parent;
      }
      if (_node->right != current) {
        _node = current;
      }
    }
    return *this;
  }

  _Self operator++(int) {
    _Self old = *this;
    operator++();
    return old;
  }

  _Self &operator--() {
    if (_node == _end) {
      while (_node->right != _end) {
        _node = _node->right;
      }
    } else if (_node->left != _end) {
      _node = _node->left;
      while (_node->right != _end) {
        _node = _node->right;
      }
    } else {
      _Node *current = _node->parent;
      while (_node == current->left) {
        _node = current;
        current = current->parent;
      }
      if (_node->left != current) {
        _node = current;
      }
    }
    return *this;
  }

  _Self operator--(int) {
    _Self old = *this;
    operator--();
    return old;
  }

  _Node *_node;
  _Node *_end;
  Compare _compare;
};

template<class Key,                     // map::key_type
    class T,                       // map::mapped_type
    class Compare = ft::less<Key>, // map::key_compare
    class Alloc =
    ft::allocator<ft::pair<const Key, T> > > // map::allocator_type
class map {
 public:
  typedef Key key_type;
  typedef T mapped_type;
  typedef ft::pair<const Key, T> value_type;
  typedef std::size_t size_type;
  typedef std::ptrdiff_t difference_type;
  typedef Compare key_compare;
  typedef Alloc allocator_type;
  typedef ft::map_iterator<value_type, Compare> iterator;
  typedef ft::map_iterator<value_type, Compare> const_iterator;
  typedef ft::reverse_iterator<iterator> reverse_iterator;
  typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef typename allocator_type::reference reference;
  typedef typename allocator_type::const_reference const_reference;
  typedef typename allocator_type::pointer pointer;
  typedef typename allocator_type::const_pointer const_pointer;

  explicit map(const key_compare &comp = key_compare(),
               const allocator_type &alloc = allocator_type())
      : _end(0), _size(0), _comp(comp), _alloc() {

    (void) alloc;
    _initEnd();
  }

  template<class InputIterator>
  map(InputIterator first, InputIterator last,
      const key_compare &comp = key_compare(),
      const allocator_type &alloc = allocator_type()) : _end(0), _size(0), _comp(comp), _alloc() {
    (void) alloc;
    _initEnd();
    insert(first, last);
  }

  map(const map &x) : _end(0), _size(0), _comp(x._comp), _alloc(x._alloc) {
    _initEnd();
    insert(x.begin(), x.end());
  }

  map &operator=(const map &x) {
    if (this != &x) {
      map tmp(x);
      swap(tmp);
    }
    return *this;
  }

  iterator begin() { return iterator(_end->left, _end); }

  const_iterator begin() const { return iterator(_end->left, _end); }

  iterator end() {
    return iterator(_end, _end);;
  }

  const_iterator end() const {
    return iterator(_end, _end);;
  }

  reverse_iterator rbegin() { return end(); }

  const_reverse_iterator rbegin() const { return end(); }

  reverse_iterator rend() { return begin(); }

  const_reverse_iterator rend() const { return begin(); }

  size_type size() const { return _size; }

  bool empty() const { return _size == 0; }

  size_type max_size() const { return _alloc.max_size(); }

  ft::pair<iterator, bool> insert(const value_type &val) {

    _node *current = _end->right;

    if (current == _end) {
      _end->right = _createNode(BLACK, _end, _end, _end, val);
      return ft::make_pair(iterator(_end->right, _end), true);
    }
    while (current != _end) {
      if (!_comp(val.first, current->data.first)) {
        if (current->right != _end) {
          current = current->right;
        } else {
          current->right = _createNode(RED, current, _end, _end, val);
          return ft::make_pair(iterator(current->right, _end), true);
        }
      } else if (val.first == current->data.first) {
        return ft::make_pair(iterator(current, _end), false);
      } else if (_comp(val.first, current->data.first)) {
        if (current->left != _end) {
          current = current->left;
        } else {
          current->left = _createNode(RED, current, _end, _end, val);
          return ft::make_pair(iterator(current->left, _end), true);
        }
      }
    }
  }

  iterator insert(iterator position, const value_type &val) {}

  template<class InputIterator>
  void insert(InputIterator first, InputIterator last) {
    while (first != last) {
      insert(*first);
      ++first;
    }
  }

  void print() const { _inorderTraversal(_end->right); }

  void swap(map &x) {
    _node tmp_end = _end;
    size_type tmp_size = _size;
    _end = x._end;
    _size = x._size;
    x._end = tmp_end;
    x._size = tmp_size;
  }

 protected:
  typedef treeNode<value_type> _node;
  typedef
  typename allocator_type::template rebind<_node>::other _allocator_type;

  _node *_createNode(Color clr = RED, _node *p = 0, _node *l = 0, _node *r = 0,
                     value_type val = value_type()) {
    _node *node = _alloc.allocate(1);
    _alloc.construct(node, val);
    node->color = clr;
    node->parent = p;
    node->left = l;
    node->right = r;
    _updateMinimum(node);
    ++_size;
    return node;
  }

  void _inorderTraversal(_node *node) const {
    if (node != _end) {
      _inorderTraversal(node->left);
      std::cout << node->data.first << ", " << node->data.second << "\n";
      _inorderTraversal(node->right);
    }
  }

  void _updateMinimum(_node *node) {
    if (_end->left == _end) {
      _end->left = node;
    } else if (_comp(node->data.first, _end->left->data.first)) {
      _end->left = node;
    }
  }

  void _initEnd() {
    _end = _alloc.allocate(1);
    _alloc.construct(_end, value_type());
    _end->color = BLACK;
    _end->parent = _end;
    _end->left = _end;
    _end->right = _end;
  }

 private:
  /*
   *  _last_node is the past-the-end element
   *  _last_node->right is a root node
   *  _last_node->left is the first (smaller) element
   */
  _node *_end;
  size_type _size;
  key_compare _comp;
  std::allocator<_node> _alloc; // TODO: change to _allocator_type
};

} // namespace ft

#endif // FT_CONTAINERS_MAP_HPP
