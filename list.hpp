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

    template<typename T, typename Allocator = std::allocator <T> >
    class List {

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

        explicit List(const allocator_type &alloc = allocator_type()) {
            initBlankList_(alloc);
        }

        explicit List(size_type n, const value_type &val = value_type(),
                      const allocator_type &alloc = allocator_type()) {
            initBlankList_(alloc);
            insert(end(), n, val);
        }

        template<class InputIterator>
        List(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) {
            initBlankList_(alloc);
            insert(end(), first, last);
        }

        List(List const &x) {
            initBlankList_(allocator_type(x.allocator_));
            insert(end(), x.begin(), x.end());
        }

        ~List() {
            clear();
            deleteNode_(last_node_);
            //TODO: check memory leaks
        }

        List &operator=(List const &x) {
            if (this != &x) {
                List(x).swap(*this);
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
            insert(first, last);
        }

        void assign(size_type n, const value_type &val) {
            clear();
            insert(n, val);
        }

        void push_front(const_reference val) {
            insert(begin(), val); //TODO: check
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
            if (pos->prev)
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
            iterator tmp = ++pos;
            if (node->prev)
                node->prev->next = node->next;
            node->next->prev = node->prev;
            deleteNode_(node);
            return tmp;
        }

        iterator erase(iterator first, iterator last) {

            if (first == end())
                return (first);
            node_pointer tmp = 0;
            node_pointer first_node = first.getNode();
            node_pointer last_node = last.getNode();
            first_node->next = last_node;
            last_node->prev = first_node;
            while (first != last) {
                tmp = first.getNode();
                ++first;
                deleteNode_(tmp);
            }
            return last;
        }

        void swap(List &x) {

            node_pointer tmp_node = last_node_;
            allocator_type tmp_allocator = allocator_;

            last_node_ = x.last_node_;
            allocator_ = x.allocator_;

            x.last_node_ = tmp_node;
            x.allocator_ = tmp_allocator;
        }

        void resize(size_type n, value_type val = value_type()) {
            if (n < size()) {
                erase(ft::advance(begin(), n), end());
            } else {
                insert(end(), n - size(), val);
            }
        }

        void clear() {
            erase(begin(), end());
        }

        /* Operations */

        void splice(iterator position, List &x) {
            splice(position, x, x.begin(), x.end());
        }

        void splice(iterator position, List &x, iterator i) {
            splice(position, x, i, ++i);
        }

        void splice(iterator position, List &x, iterator first, iterator last) {
            node_pointer pos = position.getNode();
            node_pointer pre_pos = pos->prev;
            node_pointer first_node = first.getNode();
            node_pointer last_node = last.getNode();
            if (pre_pos) {
                pre_pos->next = first_node;
                first_node->prev = pre_pos;
            } else {
                last_node_->next = first_node;
                first_node->prev = 0;
            }
            last_node->next = pos;
            pos->prev = last_node;
            x.detachNodes_(first, last);
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

        void deleteNode_(node_pointer node) {
            allocator_.destroy(node);
            allocator_.deallocate(node, 1);
        }

        void detachNodes_(iterator first, iterator last) {
            node_pointer first_node = first.getNode();
            node_pointer last_node = last.getNode();
            node_pointer new_first_node = first_node->prev;

            if (new_first_node) {
                new_first_node->next = last_node;
                last_node->prev = new_first_node;
            } else {
                last_node_->next = last_node;
            }
        }

        /**
         * @brief Initialization blank List container. Needed to avoid duplication
         */
        void initBlankList_(const allocator_type &alloc = allocator_type()) {
            allocator_ = alloc;
            last_node_ = createNode_(0);
            last_node_->next = last_node_;
            last_node_->prev = last_node_;
        }

        node_pointer last_node_;
        std::allocator <node_type> allocator_;
    };

}

#endif //FT_CONTAINERS_LIST_HPP
