#include "LCS.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <deque>

class line {
  size_t fhash;
  std::string fstr;

  public:
  line(const std::string& s)
  : fhash { std::hash<std::string>()(s) },
    fstr { s }
  { }

  const std::string& str() const
  { return fstr; }

  bool operator == (const line& other) const
  { return fhash == other.fhash; }
};

std::ostream& operator << (std::ostream& os, const line& l)
{ return os << l.str(); }


typedef std::deque<line> lines;

template <>
class LCS<lines>::prepend {
  void operator () (lines& s, const line& l)
  { s.push_front(l); }
};


lines read_lines(std::istream& is)
{
  lines ls;
  std::string buf;
  while (!is.eof()) {
    std::getline(is, buf);
    ls.emplace_back(buf);
  }
  return ls;
}

int main(int argc, char** argv)
{
  std::ifstream file;
  lines s1, s2;

  if (argc != 3) {
    std::cerr << "use: " << argv[0] << " <old-file> <new-file>" << std::endl;
    return 1;
  }

  // Read "old" file.
  file.open(argv[1]);
  s1 = read_lines(file);
  file.close();

  // Read "new" file.
  file.open(argv[2]);
  s2 = read_lines(file);
  file.close();

  // Initialize LCS.
  LCS<lines> lcs { s1, s2 };
  // Write diff-header.
  std::cout << "@@ -1," << s1.size()-1 << " +1," << s2.size()-1 << " @@\n";
  // Compute diff.
  lcs.diff(std::cout);
}
