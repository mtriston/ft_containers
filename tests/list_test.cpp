//
// Created by mtriston on 28.03.2021.
//
#include "test.hpp"

bool single_digit(int x) {
  return x < 10;
}

template<typename List>
void print_list(List &x) {
  typename List::iterator itBegin = x.begin();
  typename List::iterator itEnd = x.end();

  while (itBegin != itEnd) {
    std::cout << *itBegin << " ";
    ++itBegin;
  }
  std::cout << "\033[0m(size = " << x.size() << (x.empty() ? ", empty" : ", not empty") << ")\n";
}

void list_tests() {
  title("LIST");
  title("Test constructors and assignment operator");

  std::list<double> a;
  for (int i = 0; i <= 10; ++i) {
    a.push_back(i);
    a.push_front(i);
  }
  std::list<double> b(a);
  for (int i = 0; i <= 5; ++i) {
    b.pop_back();
    b.pop_front();
  }
  a = b;
  b.clear();
  print_list(a);

  title("Test capacity methods");

  std::cout << " a.size() = " << a.size() << std::endl;
  std::cout << " a.max_size() = " << a.max_size() << std::endl;
  std::cout << " a.empty() = " << a.empty() << std::endl;
  std::cout << " b.size() = " << b.size() << std::endl;
  std::cout << " b.max_size() = " << b.max_size() << std::endl;
  std::cout << " b.empty() = " << b.empty() << std::endl;

  title("Element access");

  print_list(a);
  std::cout << "a.front() = " << a.front() << std::endl;
  std::cout << "a.back() = " << a.back() << std::endl;
  print_list(b);
  std::cout << "b.front() = " << b.front() << std::endl;
  std::cout << "b.back() = " << b.back() << std::endl;

  title("Assign");

  print_list(b);
  b.assign(a.begin(), a.end());
  print_list(b);
  b.assign(10u, 777);
  print_list(b);

  title("Insert");

  std::cout << *b.insert(++b.begin(), 111) << std::endl;
  print_list(b);
  b.insert(b.begin(), 5u, 0);
  print_list(b);
  b.insert(b.begin(), a.begin(), ++a.begin());
  print_list(b);

  title("Erase");

  std::cout << *b.erase(b.begin()) << std::endl;
  print_list(b);

  std::list<double>::iterator begin = b.begin();
  ft::advance(begin, 5);
  print_list(b);
  b.erase(begin, b.end());
  print_list(b);

  title("Swap");

  print_list(a);
  print_list(b);
  a.swap(b);
  print_list(a);
  print_list(b);

  title("Resize");

  b.resize(3);
  print_list(b);
  b.resize(10, 555);
  print_list(b);

  title("Clear");

  b.clear();
  a.clear();

  title("Splice");

  for (int i = 1; i <= 9; ++i) {
    a.push_back(i);
    a.push_back(i);
    b.push_front(i * 10);
  }

  print_list(a);
  print_list(b);
  a.splice(a.begin(), b, b.begin(), b.end());
  print_list(a);
  print_list(b);

  print_list(a);
  print_list(b);

  b.splice(b.begin(), a);

  print_list(a);
  print_list(b);

  a.splice(a.begin(), b, b.begin());
  print_list(a);
  print_list(b);

  title("Remove");

  a = b;
  print_list(b);
  b.remove(1);
  b.remove(100);
  print_list(b);

  title("Remove if");

  b.remove_if(single_digit);
  print_list(b);

  title("Unique");

  print_list(a);
  a.unique();
  print_list(a);

  title("Merge");

  a.clear();
  b.clear();
  for (int i = 1; i <= 20; ++i) {
    if (i % 2 || i < 10) {
      a.push_back(i);
    } else {
      b.push_back(i);
    }
  }
  print_list(a);
  print_list(b);
  a.merge(b);
  print_list(a);
  print_list(b);

  a.clear();
  b.clear();
  for (int i = 1; i <= 20; ++i) {
    if (i % 2 || i < 10) {
      a.push_back(i);
    } else {
      b.push_back(i);
    }
  }
  print_list(a);
  print_list(b);
  a.merge(b, ft::less<int>());
  print_list(a);
  print_list(b);

  title("Sort");

  a.clear();
  for (int i = 0; i < 44; ++i)
    a.push_back(i % 2 == 0 ? i + 10 : i - 10);
  print_list(a);
  a.sort();
  print_list(a);
  a.sort(ft::greater<int>());
  print_list(a);

  title("Reverse");
  a.reverse();
  print_list(a);

  title("Relational operators");
  a.clear();
  b.clear();
  for (int i = 0; i < 20; ++i) {
    a.push_back(i);
    b.push_back(i);
  }
  print_list(a);
  print_list(b);
  if (a == b) std::cout << "a and b is equal\n";
  if (a >= b) std::cout << "a greater or equal to b\n";
  a.push_back(20);
  print_list(a);
  print_list(b);
  if (a > b) std::cout << "a greater than b\n";
  if (a >= b) std::cout << "a greater or equal to b\n";
  if (b < a) std::cout << "b less than a\n";
  if (b <= a) std::cout << "b less or equal to a\n";

  title("Reverse iterator");
  std::list<double>::reverse_iterator rBegin = a.rbegin();
  std::list<double>::reverse_iterator rEnd = a.rend();
  while (rBegin != rEnd) {
    std::cout << *rBegin << " ";
    ++rBegin;
  }
  std::cout << std::endl;

  title("Testing blank lists");
  a.clear();
  b.clear();
  a.sort();
  a.merge(b);
  b.reverse();
  a.swap(b);
  b.erase(b.begin(), b.end());
  b.splice(b.begin(), a);
  b.remove(0);
  b.unique();
  print_list(a);
  print_list(b);
}
