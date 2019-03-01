#include <iostream>
#include <random>

#include "forest.hpp"

typedef forest_traits<find_method::path_halving, union_method::by_size> naive_byrank;

int main() {
  size_t n = 100;

  forest<void, naive_byrank> forest { n };

  for (size_t i = 0; i < n; i++)
    forest.make_set();

  std::random_device rd;
  std::mt19937 gen { rd() };
  std::uniform_int_distribution<size_t> dis { 0, n };

  size_t nrnd = n;
  while (nrnd--)
    forest.join(dis(gen), dis(gen));

  std::cout << forest;
}
