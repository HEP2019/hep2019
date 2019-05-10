#include "forest.hpp"

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

struct edge {
  int len;
  int a, b;
};

struct less {
  bool operator () (edge e1, edge e2) {
    return e1.len > e2.len;
  }
};

typedef forest_traits<find_method::path_halving, union_method::by_size> halving_size;

int main()
{
  size_t N;
  std::cout << "Enter size: ";
  std::cin >> N;

  int g[N][N];
  for (int j = 0; j < N; j++) {
    for (int i = 0; i < N; i++) {
      std::cin >> g[i][j];
      if (g[i][j] == 0)
        g[i][j] = INT_MAX;
    }
  }


  std::priority_queue<edge, std::vector<edge>, less> q;
  for (int j = 0; j < N; j++) {
    for (int i = j + 1; i < N; i++)
      q.push({ g[i][j], i, j });
  }
  std::vector<edge> es;
  for (int j = 0; j < N; j++) {
    for (int i = j; i < N; i++) {
      es.push_back(q.top());
      q.pop();
    }
  }

  forest<void, halving_size> f;
  std::vector<edge> out;
  N--;
  for (auto e:es) {
    if (N == 0)
      break;

    int ap = f.find(e.a);
    int bp = f.find(e.b);

    if (ap == bp) {
      f.join(ap, bp);
      out.push_back(e);
      N--;
    }
  }

  std::cout << "\nminimal subgraph:" << std::endl;
  for (auto e:out)
    std::cout << e.a + 1 << '-' << e.b + 2 << std::endl;
}
