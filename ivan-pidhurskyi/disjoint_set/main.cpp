#include <iostream>
#include <random>

#include "forest.hpp"

int main() {
  size_t n = 1000;
  size_t n_gr = 10;

  forest<void> forest { n };

  for (size_t i = 0; i < n; i++)
    forest.make_set();

  std::random_device rd;
  std::mt19937 gen { rd() };
  std::uniform_int_distribution<size_t> dis { n_gr + 1, n };
  std::uniform_int_distribution<size_t> dis_gr { 0, n_gr };

  size_t nrnd = n;
  while (nrnd--)
    forest.join(dis(gen), dis(gen));

  std::cout << forest;
}
