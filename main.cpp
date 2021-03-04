#include <iostream>
#include <iomanip>
#include <string>
#include <memory>
#include "list.hpp"
#include <list>

template<typename List>
void print_list(const List &x) {
  auto itBegin = x.begin();
  auto itEnd = x.end();
  while (itBegin != itEnd) {
	std::cout << *itBegin << " ";
	++itBegin;
  }
  std::cout << std::endl;
}

void title(std::string s) {
  std::cout<<"\033[35m"<<std::setfill('-')<<std::setw(40)<<s;
  std::cout<<std::setfill('-')<<std::setw(40)<<std::string(s.length(), ' ')<< "\033[0m"<<std::endl;

}

int main() {

  title("Test constructors and assignment operator");

  ft::list<int> a;
  for (int i = 0; i <= 10; ++i) {
	a.push_back(i);
	a.push_front(i);
  }
  ft::list<int> b(a);
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
  std::cout << " b.empty() = " << b.empty() << std::endl;

  title("Element access");

  std::cout << "a.front() = " << a.front() << std::endl;
  std::cout << "a.back() = " << a.back() << std::endl;
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

  auto begin = b.begin();
  ft::advance(begin, 5);
  std::cout << *b.erase(begin, b.end()) << std::endl;
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

  a.assign(10u, 999);
  b.assign(10u, 666);

  print_list(a);
  print_list(b);

  a.splice(a.begin(), b, b.begin(), b.end());
  print_list(a);
  print_list(b);

  b.splice(b.begin(), a);
  print_list(a);
  print_list(b);

  a.splice(a.begin(), b, b.begin());
  print_list(a);
  print_list(b);
  return 0;
}
