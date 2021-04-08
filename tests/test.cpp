
#include "test.hpp"

void title(std::string s) {
  std::cout << "\033[35m" << std::setfill('-') << std::setw(40) << s;
  std::cout << std::setfill('-') << std::setw(40) << std::string(s.length(), ' ') << "\033[0m" << std::endl;

}

int main() {
  vector_tests();
  stack_tests();
  queue_tests();
  return 0;
}
