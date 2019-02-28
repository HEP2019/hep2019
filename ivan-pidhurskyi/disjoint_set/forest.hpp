#pragma once

#include <cassert>
#include <cstdlib>
#include <new>
#include <ostream>

enum class find_method
{
  naive,
  path_compression,
  path_halving,
  path_splitting,
};
enum class union_method
{
  naive,
  by_rank,
  by_size,
};
template <find_method  FindMethod,
          union_method UnionMethod>
struct forest_traits {
  static std::integral_constant<find_method, FindMethod> find;
  static std::integral_constant<union_method, UnionMethod> union_;
};

// Basic fields for element with non-void identifier.
template <typename Id>
struct element_base {
  size_t parent;
  Id name;
  element_base(size_t id, const Id& name)
  : parent { id },
    name { name }
  { }
};
// Specialization for elements without additional identifier.
template <>
struct element_base<void> {
  size_t parent;
  element_base(size_t id)
  : parent { id }
  { }
};

// Union by rank or by size needs additional field.
template <union_method>
struct element_union_part { union { size_t size; size_t rank = 0; }; };
// Naive union don't need any additional fields.
template <>
struct element_union_part<union_method::naive> { };

template <typename Id, union_method UnionMethod>
struct element: element_base<Id>, element_union_part<UnionMethod> {
  using element_base<Id>::element_base;
};

template <typename Id, typename Traits>
class forest {
  public:
  using value_type = element<Id, Traits::union_>;

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

  size_t find(size_t id);
  void join(size_t x, size_t y);

  template <typename T, typename U>
  friend std::ostream& operator << (std::ostream& , const forest<T, U>&);
  template <typename U>
  friend std::ostream& operator << (std::ostream& , const forest<void, U>&);
  template <typename A, union_method B, typename C>
  friend size_t __find(forest<A, C>& f, size_t id);
  template <typename A, find_method B, typename C>
  friend void __join(forest<A, C>& f, size_t x, size_t y);
};

template <typename Id, union_method UnionMethod,
          typename Traits = forest_traits<find_method::naive, UnionMethod>>
size_t __find(forest<Id, Traits>& f, size_t id) {
  while (id != f.fels[id].parent)
    id = f.fels[id].parent;
  return id;
}
template <typename Id, typename Traits>
size_t forest<Id, Traits>::find(size_t x) {
  return __find<Id, Traits::union_>(*this, x);
}


// Union by rank.
template <typename Id, find_method FindMethod,
          typename Traits = forest_traits<FindMethod, union_method::by_rank>>
void __join(forest<Id, Traits>& f, size_t x, size_t y) {
  auto x_root = __find<Id, Traits::union_>(f, x);
  auto y_root = __find<Id, Traits::union_>(f, y);

  if (x_root == y_root)
    return;

  // if same ranks, then rank of resulting tree will be one larger
  if (f.fels[x_root].rank == f.fels[y_root].rank) {
    f.fels[y_root].parent = x_root;
    f.fels[x_root].rank ++;
    return;
  }

  // if ranks are different, then join tree with smaller rank
  // to the tree with larger rank.
  if (f.fels[x_root].rank > f.fels[y_root].rank)
    f.fels[y_root].parent = x_root;
  else
    f.fels[x_root].parent = y_root;

  return;
}
template <typename Id, typename Traits>
void forest<Id, Traits>::join(size_t x, size_t y) {
  __join<Id, Traits::find>(*this, x, y);
}

template <typename T, typename U>
std::ostream& operator << (std::ostream& os, const forest<T, U>& f) {
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

template <typename T>
std::ostream& operator << (std::ostream& os, const forest<void, T>& f) {
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

