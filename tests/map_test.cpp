//
// Created by mtriston on 08.04.2021.
//
#include <map>
#include "test.hpp"

template<class Map>
void print(Map const &c) {
  typename Map::const_iterator b = c.begin();
  typename Map::const_iterator e = c.end();
  std::cout << "(size = " << c.size() << ", empty = " << (c.empty() ? "true" : "false") << ") ";
  while (b != e) {
    std::cout << "Key = \"" << b->first << "\", Value = \"" << b->second << "\" | ";
    ++b;
  }
  std::cout << "\n";
}

void map_tests() {

title("MAP");
title("Constructors");
ft::map<int, std::string> a;
for (int i = 0; i < 10; ++i) {
  a.insert(ft::make_pair(i, "test"));
}
ft::map<int, std::string> b(a);
b.erase(b.begin());
b = a;
print(a);
print(b);
title("Iterators");
  {
    ft::map<int, std::string>::iterator b = a.begin();
    ft::map<int, std::string>::iterator e = a.end();
    while (b != e) {
      std:: cout << (*b).first << ", " << (*b).second << " ";
      ++b;
    }
    std::cout << std::endl;
  }
  {
    ft::map<int, std::string>::reverse_iterator b = a.rbegin();
    ft::map<int, std::string>::reverse_iterator e = a.rend();
    while (b != e) {
      std:: cout << (*b).first << ", " << (*b).second << " ";
      ++b;
    }
    std::cout << std::endl;
  }
  title("Capacity");
  a.clear();
  print(a);
  std::cout << "max_size = " << a.max_size() << std::endl;

  title("Element access");
  for (int i = 0; i < 10; ++i) {
    a.insert(ft::make_pair(i, "test"));
  }
  print(a);
  std::cout << a[0] << std::endl;
  a[0] = "hello";
  std::cout << a[0] << std::endl;
  a[20] = "bye";
  print(a);
  title("Insert");
  std::cout << a.insert(ft::make_pair(13, "New")).second << std::endl;
  std::cout << a.insert(ft::make_pair(13, "New")).second << std::endl;
  a.insert(a.begin(),ft::make_pair(13, "New"));
  b.clear();
  b.insert(a.begin(), a.end());
  print(b);
  title("Erase");
 b.erase(b.begin());
 print(b);
 b.erase(13);
 print(b);
 b.erase(b.begin(), b.end());
 print(b);
 title("Swap");
 a.swap(b);
 print(a);
 print(b);
 title("Observers");
 std::cout << a.key_comp()(1,1) << std::endl;
 std::cout << a.value_comp()(ft::make_pair(1, "1"), ft::make_pair(1, "2")) << std::endl;
}