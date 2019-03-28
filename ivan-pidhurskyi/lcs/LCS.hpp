#pragma once

#include <cstddef>
#include <vector>
#include <ostream>

template <typename T>
class LCS {
  size_t** fcs;
  size_t fm, fn;
  T fs1, fs2;

  private:
  void _get(size_t i, size_t j, std::vector<T>& ret, size_t idx) const;
  void _diff(std::ostream& os, size_t i, size_t j) const;

  public:
  class concat;
  explicit LCS(const T& s1, const T& s2);
  ~LCS();

  std::vector<T> get() const;
  void           diff(std::ostream& os) const;

  template <typename U>
  friend std::ostream& operator << (std::ostream& os, const LCS<U>& lcs);
};



/*_____________________________________________________________________________
 *                           Implementation
 */
template <typename T>
LCS<T>::LCS(const T& s1, const T& s2)
: fm { s1.size() }, // N-rows
  fn { s2.size() }, // N-cols
  fs1 { s1 },
  fs2 { s2 }
{
  fcs = new size_t* [fm + 1];
  for (size_t i = 0; i <= fm; ++i)
    fcs[i] = new size_t [fn + 1];

  for (size_t i = 1; i <= fm; ++i) {
    for (size_t j = 1; j <= fn; ++j) {
      size_t cu = fcs[i][j-1],
             cl = fcs[i-1][j];
      fcs[i][j] = std::max(cu, cl) + (s1[i-1] == s2[j-1]);
    }
  }
}

template <typename T>
LCS<T>::~LCS()
{
  for (size_t i = 0; i <= fm; ++i)
    delete[] fcs[i];
  delete[] fcs;
}

template <typename T>
void LCS<T>::_get(size_t i, size_t j, std::vector<T>& ret, size_t idx) const
{
  if (i == 0 || j == 0)
    return;

  size_t cu = fcs[i][j-1],
         cl = fcs[i-1][j];

  if (fs1[i-1] == fs2[j-1]) {
    ret[idx] = concat()(fs1[i-1], ret[idx]); // append character
    _get(i-1, j-1, ret, idx); // continue with prefix
  } else if (cu > cl) {
    _get(i, j-1, ret, idx); // seek up
  } else if (cu < cl) {
    _get(i-1, j, ret, idx); // seek left
  } else {
    // branching
    ret.emplace_back(ret[idx]); // create new string
    _get(i, j-1, ret, ret.size()-1); // build new string
    _get(i-1, j, ret, idx); // continue current string
  }
}

template <typename T>
std::vector<T> LCS<T>::get() const
{
  std::vector<T> ret (1);
  _get(fm, fn, ret, 0);
  return ret;
}

template <typename T>
void LCS<T>::_diff(std::ostream& os, size_t i, size_t j) const
{
  if (i > 0 and j > 0 and fs1[i-1] == fs2[j-1]) {
    _diff(os, i-1, j-1);
    os << "  " << fs1[i-1] << std::endl;
  } else if (j > 0 and (i == 0 or fcs[i][j-1] >= fcs[i-1][j])) {
    _diff(os, i, j-1);
    os << "\e[38;5;2m+ " << fs2[j-1] << "\e[0m" << std::endl;
  } else if (i > 0 and (j == 0 or fcs[i][j-1] < fcs[i-1][j])) {
    _diff(os, i-1, j);
    os << "\e[38;5;1m- " << fs1[i-1] << "\e[0m" << std::endl;
  }
}

template <typename T>
void LCS<T>::diff(std::ostream& os) const
{ _diff(os, fm, fn); }

template <typename T>
std::ostream& operator << (std::ostream& os, const LCS<T>& lcs)
{
  os << "    ";
  for (size_t i = 0; i < lcs.fm; ++i)
    os << "\e[38;5;255;1m" << lcs.fs1[i] << "\e[0m ";
  os << std::endl;

  for (size_t j = 0; j <= lcs.fn; ++j) {
    os << "\e[38;5;255;1m" << (j == 0 ? ' ' : lcs.fs2[j - 1]) << "\e[0m ";
    for (size_t i = 0; i <= lcs.fm; ++i)
      os << lcs.fcs[i][j] << " ";
    os << std::endl;
  }
  return os;
}
