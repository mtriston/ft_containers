#include <iostream>
#include <memory>
#include "List.hpp"
#include <list>

template<typename List>
void print_list(const List &x) {
    auto itBegin = x.begin();
    auto itEnd = x.end();
    while (itBegin != itEnd) {
        std::cout << *itBegin << std::endl;
        ++itBegin;
    }
}

int main() {

/* Test constructors and assignment operator */

    ft::List<int> a;
    for (int i = 0; i <= 10; ++i) {
        a.push_back(i);
        a.push_front(i);
    }
    ft::List<int> b(a);
    for (int i = 0; i <= 5; ++i) {
        b.pop_back();
        b.pop_front();
    }
    a = b;
    b.clear();
    print_list(a);

    /* Test capacity methods */
    std::cout << " a.size() = " << a.size() << std::endl;
    std::cout << " a.max_size() = " << a.max_size() << std::endl;
    std::cout << " a.empty() = " << a.empty() << std::endl;
    std::cout << " b.empty() = " << b.empty() << std::endl;

    /* Element access */
    std::cout << "a.front() = " << a.front() << std::endl;
    std::cout << "a.back() = " << a.back() << std::endl;
    std::cout << "b.front() = " << b.front() << std::endl;
    std::cout << "b.back() = " << b.back() << std::endl;

    return 0;
}
