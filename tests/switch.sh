if grep "ft::vector" ./vector_test.cpp; then
  sed -i 's/ft::vector/std::vector/g' vector_test.cpp
  sed -i 's/ft::list/std::list/g' list_test.cpp
  sed -i 's/ft::map/std::map/g' map_test.cpp
  sed -i 's/ft::make_pair/std::make_pair/g' map_test.cpp
  sed -i 's/ft::stack/std::stack/g' stack_test.cpp
  sed -i 's/ft::queue/std::queue/g' queue_test.cpp
else
  sed -i 's/std::vector/ft::vector/g' vector_test.cpp
  sed -i 's/std::list/ft::list/g' list_test.cpp
  sed -i 's/std::map/ft::map/g' map_test.cpp
  sed -i 's/std::make_pair/ft::make_pair/g' map_test.cpp
  sed -i 's/std::stack/ft::stack/g' stack_test.cpp
  sed -i 's/std::queue/ft::queue/g' queue_test.cpp
fi