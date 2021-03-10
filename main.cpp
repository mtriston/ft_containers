#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "list.hpp"
#include <list>

bool single_digit (const int& value) { return (value<10); }

bool binary_pred1(const int &x, const int &y) { return x == y; }

bool is_big(const int &x, const int &y) { return x >= y; }

bool compare(int x, int y) { return x > y; }

template<typename List>
void print_list(const List &x) {
  auto itBegin = x.begin();
  auto itEnd = x.end();

  std::cout << "print list: ";
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

  auto begin = b.begin();
  ft::advance(begin, 5);
  print_list(b);
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

  for(int i = 1; i <= 9; ++i) {
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
  a.unique(binary_pred1);
  print_list(a);

  title("Merge");

  a.clear();
  b.clear();
  for (int i = 1; i < 20; ++i) {
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
  for (int i = 20; i > 0; --i) {
	if (i % 2 || i < 10) {
	  a.push_back(i);
	} else {
	  b.push_back(i);
	}
  }
  print_list(a);
  print_list(b);
  a.merge(b, compare);
  print_list(a);
  print_list(b);

  title("Sort");

  a.clear();
  std::srand(time(NULL));
  for (int i = 0; i < 20; ++i)
    a.push_back(std::rand() % 100);
  print_list(a);
  a.sort();
  print_list(a);
  a.sort(is_big);
  print_list(a);
  return 0;
}