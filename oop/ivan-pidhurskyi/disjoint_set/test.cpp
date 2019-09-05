#include <iostream>
#include <string>
#include <climits>

#include "forest.hpp"

typedef forest_traits<find_method::path_halving, union_method::by_size> halving_size;

int main()
{
  forest<void, halving_size> forest { 10 };

  for (int i = 0; i < 10; i++)
    forest.make_set();

  std::string cmd;
  size_t p[2];

  while (true) {
    std::cout << "idx:    [ ";
    for (int i = 0; i < 10; i++)
      std::cout << i << ' ';
    std::cout << ']' << std::endl;
    std::cout << "parent: [ ";
    for (int i = 0; i < 10; i++)
      std::cout << forest.find(i) << ' ';
    std::cout << ']' << std::endl;

    std::cout << "> ";
    std::cin >> cmd;
    if (std::cin.eof())
      break;
    if (cmd == "find") {
      std::cin >> p[0];
      std::cout << forest.find(p[0]) << std::endl;
    } else if (cmd == "union") {
      std::cin >> p[0] >> p[1];
      forest.join(p[0], p[1]);
    } else if (cmd == "same?") {
      std::cin >> p[0] >> p[1];
      bool same = (forest.find(p[0]) == forest.find(p[1]));
      std::cout << std::boolalpha << same << std::endl;
    } else {
      std::cout << "commands:" << std::endl
                << "\tfind <idx>" << std::endl
                << "\tunion <idx #1> <idx #2>" << std::endl
                << "\tsame? <idx #1> <idx #2>" << std::endl;
    }
    std::cout << std::endl;
    std::cin.ignore(INT_MAX, '\n');
  }
}
