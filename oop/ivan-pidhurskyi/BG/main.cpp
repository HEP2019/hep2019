#include <iostream>
#include <vector>

typedef unsigned long int color_t;

class counter {
  public:
  typedef color_t           key_type;
  typedef int               value_type;
  typedef value_type&       reference;

  private:
  /* Element-type of main buffer which resolves hash-collisions. */
  class bucket {
    typedef std::pair<key_type,value_type> pair;
    std::vector<pair> m_vec;

    public:
    /* Return value corresponding to given key. */
    value_type operator [] (key_type key) const
    {
      for (size_t i = 0; i < m_vec.size(); ++i) {
        if (m_vec[i].first == key)
          // found matching key
          return m_vec[i].second;
      }
      // no suck key => count equals zero
      return 0;
    }
    reference operator [] (key_type key)
    {
      for (size_t i = 0; i < m_vec.size(); ++i) {
        if (m_vec[i].first == key)
          // found matching key
          return m_vec[i].second;
      }
      // no such key => insert new cell with count initialized to zero
      m_vec.push_back(pair (key, 0));
      return m_vec.back().second;
    }
  };

  const size_t m_cap;
  bucket* const   m_buf;

  /* hide unsafe operations */
  counter(const counter&);
  counter& operator = (const counter&);

  /* Return index of bucket for given key. */
  key_type bucket_idx(key_type key) const { return key % m_cap; }

  /* Element access. */
  value_type _at(size_t key) const
  { return m_buf[bucket_idx(key)][key]; }
  reference  _at(size_t key)
  { return m_buf[bucket_idx(key)][key]; }

  public:
  /* Construct hash-map with optimal buffer length for `cap`-inserts. */
  explicit counter(size_t cap)
  : m_cap (cap * 1.61),  m_buf (new bucket[m_cap])
  { }
  ~counter() { delete[] m_buf; }

  /* Element access interface. */
  value_type operator [] (size_t key) const { return _at(key); }
  reference  operator [] (size_t key)       { return _at(key); }

  /* Increment counter for given key. */
  void insert(key_type key) { _at(key) += 1; }
};

int main()
{
  int n;
  color_t color;

  std::cin >> n;
  counter cnt (n);

  for (int i = 0; i < n; ++i) {
    std::cin >> color;
    cnt.insert(color);
  }

  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    std::cin >> color;
    std::cout << cnt[color] << ' ';
  }
  std::cout << std::endl;
}
