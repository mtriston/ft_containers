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
  std::map<int, std::string> a;
  for (int i = 0; i < 10; ++i) {
    a.insert(std::make_pair(i, "test"));
  }
  std::map<int, std::string> b(a);
  b.erase(b.begin());
  b = a;
  print(a);
  print(b);
  title("Iterators");
  {
    std::map<int, std::string>::iterator b = a.begin();
    std::map<int, std::string>::iterator e = a.end();
    while (b != e) {
      std::cout << (*b).first << ", " << (*b).second << " ";
      ++b;
    }
    std::cout << std::endl;
  }
  {
    std::map<int, std::string>::reverse_iterator b = a.rbegin();
    std::map<int, std::string>::reverse_iterator e = a.rend();
    while (b != e) {
      std::cout << (*b).first << ", " << (*b).second << " ";
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
    a.insert(std::make_pair(i, "value" + std::string(1, i + '0')));
  }
  print(a);
  std::cout << a[0] << std::endl;
  a[0] = "hello";
  std::cout << a[0] << std::endl;
  a[20] = "bye";
  print(a);
  title("Insert");
  std::cout << a.insert(std::make_pair(13, "New")).second << std::endl;
  std::cout << a.insert(std::make_pair(13, "New")).second << std::endl;
  a.insert(a.begin(), std::make_pair(13, "New"));
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
  std::cout << a.key_comp()(1, 1) << std::endl;
  std::cout << a.value_comp()(std::make_pair(1, "1"), std::make_pair(1, "2")) << std::endl;
  title("Operations");
  std::cout << b.find(1)->second << std::endl;
  //std::cout << b.find(-1)->second << std::endl;

  std::cout << b.count(1) << std::endl;
  //std::cout << b.count(-1) << std::endl << std::endl;

  std::cout << b.lower_bound(2)->second << std::endl;
//  std::cout << b.lower_bound(40)->second << std::endl;

  std::cout << b.upper_bound(1)->second << std::endl;
//  std::cout << b.upper_bound(40)->second << std::endl;

  std::cout << b.equal_range(1).first->second << std::endl;
  std::cout << b.equal_range(1).second->second << std::endl;

//  std::cout << b.equal_range(111).first->second << std::endl;
//  std::cout << b.equal_range(111).second->second << std::endl;

}