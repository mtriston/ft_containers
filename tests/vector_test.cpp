//
// Created by mtriston on 28.03.2021.
//

#include "test.hpp"

template<typename Container>
void print_vector(std::string const &msg, Container &x) {
  typename Container::iterator itBegin = x.begin();
  typename Container::iterator itEnd = x.end();

  std::cout << msg << ": " << "\033[34m";
  while (itBegin != itEnd) {
    std::cout << *itBegin << " ";
    ++itBegin;
  }
  std::cout << "\033[0m(size = " << x.size() << ", capacity = " << x.capacity()
            << (x.empty() ? ", empty" : ", not empty") << ")\n";
}

static void constructors() {

  title("Constructors");

  ft::vector<int> a;
  print_vector("Default constructor", a);

  ft::vector<std::string> b(5, "Vector");
  print_vector("Fill constructor", b);

  ft::vector<std::string> c(++b.begin(), b.end());
  print_vector("Range constructor", c);

  ft::vector<int> d(a.begin(), a.end());
  print_vector("Range constructor with blank range", d);

  ft::vector<std::string> e(c);
  print_vector("Copy constructor", e);

  ft::vector<int> f(d);
  print_vector("Copy constructor with blank vector", f);

  e = b;
  print_vector("Assigment operator", e);

  f = d;
  print_vector("Assigment operator with blank vector", f);

}

static void iterators() {

  title("Iterators");

  ft::vector<int> a;
  for (int i = 0; i <= 10; ++i)
    a.push_back(i);

  const ft::vector<int> b(a);

  std::cout << "print with iterator" << "\n";
  ft::vector<int>::const_iterator it_begin = b.begin();
  ft::vector<int>::const_iterator it_end = b.end();

  while (it_begin != it_end) {
    std::cout << *it_begin++ << " ";
  }
  std::cout << "\n";

  ft::vector<int>::const_reverse_iterator it_rbegin = b.rbegin();
  ft::vector<int>::const_reverse_iterator it_rend = b.rend();

  std::cout << "print with reverse iterator" << "\n";
  while (it_rbegin != it_rend) {
    std::cout << *it_rbegin++ << " ";
  }
  std::cout << "\n";
}

static void capacity() {
  title("Capacity");
  ft::vector<int> a;
  std::cout << "a.max_size() = " << a.max_size() << "\n";
  print_vector("Blank container 'a'", a);
  a.reserve(10);
  print_vector("Container 'a' after reserve(10)", a);
  ft::vector<int> b(5u, 666);
  print_vector("Container 'b'", b);
  b.resize(2);
  print_vector("Container 'b' after resize(2)", b);
  b.resize(7, 111);
  print_vector("Container 'b' after resize(7, 111)", b);
  b.reserve(9);
  print_vector("Container 'b' after reserve(9)", b);
}

static void element_access() {

  title("Element access");

  ft::vector<int> a;
  for (int i = 1; i < 10; ++i) {
    std::cout << "capacity: " << a.capacity() << " ";
    a.push_back(i);
  }
  print_vector("Vector 'a'", a);
  std::cout << "a[0] = " << a[0] << std::endl;
  std::cout << "a[3] = " << a[3] << std::endl;
  a[3] = 333;
  std::cout << "a[3] after change value = " << a[3] << std::endl;
  try {
    std::cout << "a.at(10) = " << a.at(10) << std::endl;
  } catch (std::exception &e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "a.front() = " << a.front() << std::endl;
  std::cout << "a.back() = " << a.back() << std::endl;
}

static void modifiers() {
  title("Modifiers");

  ft::vector<int> a(10u, 111);
  print_vector("Vector 'a'", a);
  a.assign(5u, 999);
  print_vector("Vector 'a' after asign(5, 999)", a);
  ft::vector<int> b;
  b.assign(++a.begin(), a.end());
  print_vector("Vector 'b' after assign(++a.begin(), a.end())", b);

  for (int i = 0; i < 10; ++i)
    a.push_back(i);
  print_vector("Vector 'a' after push_back(i) from 0 to 9", a);

  for (int i = 0; i < 10; ++i)
    a.pop_back();
  print_vector("Vector 'a' after 10 times pop_back()", a);

  std::cout << "(return value: " << *a.insert(a.end(), 333) << ") ";
  print_vector("Vector 'a' after insert(a.end(), 333) and insert(a.begin(), 10u, 999)", a);
  b.clear();
  b.insert(b.end(), a.begin(), a.end());
  print_vector("Blank vector 'b' after insert(b.end(), a.begin(), a.end())", b);

  b.erase(--b.end());
  print_vector("Vector 'b' after erase(--b.end())", b);
  std::cout << "(return value: " << *b.erase(++b.begin(), b.end() - 2) << ") ";
  print_vector("Vector 'b' after erase(++b.begin(), b.end() - 2)", b);

  print_vector("Vector 'a'", a);
  print_vector("Vector 'b'", b);
  a.swap(b);
  print_vector("Vector 'a' after swap()", a);
  print_vector("Vector 'b' after swap()", b);
//	ft::swap(a, b);
  print_vector("Vector 'a' after swap()", a);
  print_vector("Vector 'b' after swap()", b);

  a.clear();
  b.clear();
  print_vector("Vector 'a' after clear()", a);
  print_vector("Vector 'b' after clear()", b);
}

static void relational_operators() {
  title("Relational operators");
  ft::vector<std::string> a(10, "Vector");
  ft::vector<std::string> b(a);
  print_vector("Vector 'a'", a);
  print_vector("Vector 'b'", b);
  std::cout << "a == b is " << (a == b ? "true" : "false") << "\n";
  std::cout << "a != b is " << (a != b ? "true" : "false") << "\n";
  std::cout << "a < b is " << (a < b ? "true" : "false") << "\n";
  std::cout << "a <= b is " << (a <= b ? "true" : "false") << "\n";
  std::cout << "a >= b is " << (a >= b ? "true" : "false") << "\n";
  std::cout << "a > b is " << (a > b ? "true" : "false") << "\n";
  a.pop_back();
  print_vector("Vector 'a'", a);
  print_vector("Vector 'b'", b);
  std::cout << "a == b is " << (a == b ? "true" : "false") << "\n";
  std::cout << "a != b is " << (a != b ? "true" : "false") << "\n";
  std::cout << "a < b is " << (a < b ? "true" : "false") << "\n";
  std::cout << "a <= b is " << (a <= b ? "true" : "false") << "\n";
  std::cout << "a >= b is " << (a >= b ? "true" : "false") << "\n";
  std::cout << "a > b is " << (a > b ? "true" : "false") << "\n";
};

void vector_tests() {
  title("VECTOR");
  constructors();
  iterators();
  capacity();
  element_access();
  modifiers();
  relational_operators();
}

