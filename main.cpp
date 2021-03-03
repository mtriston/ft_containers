#include <iostream>
#include <memory>
//#include "List.hpp"
#include <list>

int main() {

  std::list<int> a;

  for (int i = 0; i <= 10; ++i)
    a.push_front(i);

  a.erase(a.begin(), a.end());
  auto begin = a.begin();
  auto end = a.end();

  while (begin != end) {
    std::cout << *begin++ << std::endl;
  }
//  ft::List<int> b;
//
//  for (int i = 0; i <= 10; ++i) {
//	b.push_back(i);
//  }
//
//  ft::List<int>::iterator itBegin(b.begin());
//  ft::List<int>::iterator itEnd(b.end());
//  while (itBegin != itEnd) {
//    std::cout << *itBegin << std::endl;
//    ++itBegin;
//  }
  return 0;
}
