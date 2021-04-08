#include "test.hpp"

void stack_tests() {
  title("STACK");

  ft::stack<int, ft::vector<int> > a;
  ft::stack<int> b;

  title("Empty");
  std::cout << "a.empty() = " << (a.empty() ? "true" : "false") << std::endl;

  std::cout << "b.push(1)\n";
  b.push(1);
  std::cout << "b.empty() = " << (b.empty() ? "true" : "false") << std::endl;

  title("Size");
  std::cout << "a.size() = " << a.size() << std::endl;

  std::cout << "b.size() = " << b.size() << std::endl;

  title("Top");
  std::cout << "b.top() = " << b.top() << std::endl;

  title("Pop");
  std::cout << "b.size() = " << b.size() << std::endl;
  std::cout << "b.pop()\n";
  b.pop();
  std::cout << "b.size() = " << b.size() << std::endl;

  title("Push");
  std::cout << "b.push(1)\n";
  b.push(1);
  std::cout << "b.top() = " << b.top() << std::endl;
  std::cout << "b.size() = " << b.size() << std::endl;
  std::cout << "b.push(2)\n";
  b.push(2);
  std::cout << "b.top() = " << b.top() << std::endl;
  std::cout << "b.size() = " << b.size() << std::endl;
  std::cout << "b.push(3)\n";
  b.push(3);
  std::cout << "b.top() = " << b.top() << std::endl;
  std::cout << "b.size() = " << b.size() << std::endl;

  title("Relational operators");

  std::cout << "a == b is " << (a == b ? "true" : "false") << "\n";
  std::cout << "a != b is " << (a != b ? "true" : "false") << "\n";
  std::cout << "a < b is " << (a < b ? "true" : "false") << "\n";
  std::cout << "a <= b is " << (a <= b ? "true" : "false") << "\n";
  std::cout << "a >= b is " << (a >= b ? "true" : "false") << "\n";
  std::cout << "a > b is " << (a > b ? "true" : "false") << "\n";
  std::cout << "b.pop() x 3 " << std::endl;
  b.pop();
  b.pop();
  b.pop();
  std::cout << "a == b is " << (a == b ? "true" : "false") << "\n";
  std::cout << "a != b is " << (a != b ? "true" : "false") << "\n";
  std::cout << "a < b is " << (a < b ? "true" : "false") << "\n";
  std::cout << "a <= b is " << (a <= b ? "true" : "false") << "\n";
  std::cout << "a >= b is " << (a >= b ? "true" : "false") << "\n";
  std::cout << "a > b is " << (a > b ? "true" : "false") << "\n";
}
