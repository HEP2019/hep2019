#pragma once

#include <cassert>
#include <cstdlib>
#include <new>
#include <ostream>

template <typename Id>
struct element {
  size_t parent;
  size_t rank;
  size_t size;
  Id name;

  element(size_t id, const Id& name)
  : parent { id },
    rank { 0 },
    size { 1 },
    name { name }
  { }
};

template <>
struct element<void> {
  size_t parent;
  size_t rank;
  size_t size;

  element(size_t id)
  : parent { id },
    rank { 0 },
    size { 1 }
  { }
};

template <typename Id>
class forest {
  public:
  using value_type = element<Id>;

  private:
  value_type* fels;
  size_t fsize;
  size_t fcap;

  public:
  explicit forest(size_t cap = 42)
  : fels { (value_type*)malloc(cap * sizeof(value_type)) },
    fsize { 0 },
    fcap { cap }
  {
    assert(fels);
  }

  forest(const forest& other)
  : fels { (value_type*)malloc(other.fcap * sizeof(value_type)) },
    fsize { other.fsize },
    fcap { other.fcap }
  {
    assert(fels);
    for (size_t i = 0; i < fsize; i++)
      fels[i] = other.fels[i];
  }

  forest(forest&& other)
  : fels { other.fels },
    fsize { other.fsize },
    fcap { other.fcap }
  {
    other.fels = nullptr;
    other.fsize = 0;
    other.fcap = 0;
  }
  ~forest() {
    if (!fsize)
      return;

    for (size_t i = 0; i < fsize; i++)
      fels[i].~value_type();
    free(fels);
  }

  public:
  template <typename T>
  size_t make_set(const T& name) {
    assert(fsize < fcap);
    new (fels + fsize) value_type { fsize, name };
    return fsize++;
  }
  size_t make_set() {
    assert(fsize < fcap);
    new (fels + fsize) value_type { fsize };
    return fsize++;
  }

  size_t find(size_t id) {
    while (id != fels[id].parent)
      id = fels[id].parent;
    return id;
  }

  // Union by rank.
  void join(size_t x, size_t y) {
    auto x_root = find(x);
    auto y_root = find(y);

    if (x_root == y_root)
      return;

    // if same ranks, then rank of resulting tree will be one larger
    if (fels[x_root].rank == fels[y_root].rank) {
      fels[y_root].parent = x_root;
      fels[x_root].rank ++;
      return;
    }

    // if ranks are different, then join tree with smaller rank
    // to the tree with larger rank.
    if (fels[x_root].rank > fels[y_root].rank)
      fels[y_root].parent = x_root;
    else
      fels[x_root].parent = y_root;

    return;
  }

  template <class T>
  friend std::ostream& operator << (std::ostream& , const forest<T>&);
};

template <typename T>
std::ostream& operator << (std::ostream& os, const forest<T>& f) {
  os << "digraph g {" << std::endl;
  //os << "\t graph [rankdir=LR];" << std::endl;
  for (size_t i = 0; i < f.fsize; i++) {
    if (f.fels[i].parent == i)
      //os << '\t' << f.fels[i].name;
      continue;
    else
      os << '\t' << f.fels[i].name << " -> " << f.fels[f.fels[i].parent].name;
  }
  return os << '}' << std::endl;
}

template <>
std::ostream& operator << (std::ostream& os, const forest<void>& f) {
  os << "digraph g {" << std::endl;
  //os << "\t graph [rankdir=LR];" << std::endl;
  for (size_t i = 0; i < f.fsize; i++) {
    if (f.fels[i].parent == i)
      //os << '\t' << i;
      continue;
    else
      os << '\t' << i << " -> " << f.fels[i].parent;
    os << ';' << std::endl;
  }
  return os << '}' << std::endl;
}

