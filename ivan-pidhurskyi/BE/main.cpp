#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstring>

double distance(int x1, int y1, int x2, int y2)
{
  return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

class field {
  int** m_cells;
  size_t m_width, m_height;
  size_t m_step;
  bool m_evolved;

  int at(int x, int y) const
  {
    if (x < 0 | y < 0 | x >= m_width | y >= m_height)
      return -1;
    else
      return m_cells[x][y];
  }

  int iswhite(int c) const { return c == 0 || c == m_step; }
  int isblack(int c) const { return !iswhite(c); }

  int evolve_at(int x, int y)
  {
    if (isblack(at(x,y)))
      return at(x,y);

    int uu = isblack( at(x+0, y-1) );
    //int ur = isblack( at(x+1, y-1) );
    int rr = isblack( at(x+1, y-0) );
    //int dr = isblack( at(x+1, y+1) );
    int dd = isblack( at(x+0, y+1) );
    //int dl = isblack( at(x-1, y+1) );
    int ll = isblack( at(x-1, y+0) );
    //int ul = isblack( at(x-1, y-1) );
    int nblack4 = uu + rr + dd + ll;
    //int nblack8 = nblack4 + ur + dr + dl + ul;

    //if (uu && dd && !ll && !rr) goto l_black;
    //if (ll && rr && !uu && !dd) goto l_black;
    if (nblack4 >= 1)
      goto l_black;

l_white:
    return 0;
l_black:
    m_evolved = true;
    return m_step;
  }

  public:
  explicit field(size_t w, size_t h)
  : m_width(w), m_height(h), m_step(1)
  {
    m_cells = new int*[w];
    for (size_t x = 0; x < w; ++x)
      m_cells[x] = new int[h];
  }

  ~field()
  {
    for (size_t x = 0; x < m_width; ++x)
      delete[] m_cells[x];
    delete[] m_cells;
  }

  size_t n_steps() const { return m_step; }
  size_t width()   const { return m_width; }
  size_t height()  const { return m_height; }

  /*
   * Perform iteration for all cells.
   */
  bool evolve()
  {
    m_evolved = false;

    for (size_t x = 0; x < m_width; ++x) {
      for (size_t y = 0; y < m_height; ++y)
        m_cells[x][y] = evolve_at(x, y);
    }

    if (m_evolved)
      m_step++;
    return m_evolved;
  }

  /*
   * Draw beautiful picture of given solution.
   */
  void circle(std::ostream& os, size_t x0, size_t y0, size_t r)
  {
    for (size_t y = 0; y < m_height; ++y) {
      for (size_t x = 0; x < m_width; ++x) {
        int v = m_cells[x][y];
        
        if (ceil(distance(x, y, x0, y0)) <= r)
          os << "\x1b[4m";
        if (x0 == x && y0 == y)
          os << "\x1b[38;5;4;1m";

        if (v < 0) {
          os << std::setw(2) << '.';
        } else if (v == 0) {
          os << "\x1b[38;5;255;1m" << std::setw(2) << v;
        } else if (v == m_step - 1) {
          if (!(x0 == x && y0 == y))
            os << "\x1b[38;5;3;1m";
          os << std::setw(2) << v;
        } else {
          os << "\x1b[1m" << std::setw(2) << v << "\x1b[0m";
        }

        os << "\x1b[0m";
      }
      os << '\n';
    }
  }

  /*
   * Return position of some cell from the latest generation.
   */
  void find_center(int& x0, int& y0) const
  {
    for (size_t y = 0; y < m_height; ++y) {
      for (size_t x = 0; x < m_width; ++x) {
        if (m_cells[x][y] == m_step - 1) {
          x0 = x;
          y0 = y;
          return;
        }
      }
    }
  }

  /*
   * Return the radius of the circle with center at { `x0`, `y0` }.
   */
  int find_radius(int x0, int y0) const
  {
    int rank = m_step - 1;
    int r = rank;
    int tmp;
    for (int y = y0 - rank; y <= y0 + rank; ++y) {
      for (int x = x0 - rank; x <= x0 + rank; ++x) {
        if (at(x, y) < 0) {
          tmp = ceil(distance(x, y, x0, y0));
          if (tmp <= r)
            r = std::min(r, tmp - 1);
        }
      }
    }
    return r;
  }

  friend std::istream& operator >> (std::istream& is, field& f);
  friend std::ostream& operator << (std::ostream& os, const field& f);
};

/*
 * Read the picture.
 */
std::istream& operator >> (std::istream& is, field& f)
{
  std::string s;
  for (size_t y = 0; y < f.m_height; ++y) {
    is >> s;
    for (size_t x = 0; x < f.m_width; ++x)
      f.m_cells[x][y] = (s[x] == '.') ? -1 : 0;
  }
  return is;
}

/*
 * Print the picture.
 */
std::ostream& operator << (std::ostream& os, const field& f)
{
  for (size_t y = 0; y < f.m_height; ++y) {
    for (size_t x = 0; x < f.m_width; ++x) {
      int v = f.m_cells[x][y];
      if (v != 0)
        os << "\x1b[38;5;232m▐▌\x1b[0m";
        //os << "\x1b[38;5;232;48;5;232m██\x1b[0m";
      else
        os << "\x1b[38;5;255m▐▌\x1b[0m";
        //os << "\x1b[38;5;255;48;5;255m██\x1b[0m";
    }
    os << '\n';
  }
  return os;
}

int main(int argc, char** argv)
{
  bool verbose = false;
  if (argc > 1 && (strcmp(argv[1], "-v") == 0 ||
                   strcmp(argv[1], "--verbose") == 0 ||
                   strcmp(argv[1], "-verbose") == 0))
  {
    verbose = true;
  }

  size_t width, height;
  std::cin >> width >> height;

  field f (width, height);
  std::cin >> f;

  // print input
  if (verbose) {
    for (int i = 0; i < f.width(); ++i)
      std::cout << "==";
    std::cout << std::endl;
    std::cout << f;
    for (int i = 0; i < f.width(); ++i)
      std::cout << "==";
    std::cout << std::endl;
  }

  // run cellular automaton
  while (f.evolve());

  // identify biggest circle
  int x0, y0;
  f.find_center(x0, y0);
  int r = f.find_radius(x0, y0);

  if (verbose) {
    f.circle(std::cout, x0, y0, r);
    for (int i = 0; i < f.width(); std::cout << "==", ++i);
    std::cout << std::endl;
    std::cout << "n steps: " << f.n_steps() << std::endl;
    std::cout << "R { " << x0 << ", " << y0 << " } = " << r << std::endl;
  } else {
    std::cout << r << std::endl;
  }
}
