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
class LCS<lines>::concat {
  lines&& operator () (const line& l, lines& s)
  {
    s.push_front(l);
    return std::move(s);
  }
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
    std::cerr << "use: " << argv[0] << " <file1> <file2>" << std::endl;
    return 1;
  }

  // read first file
  file.open(argv[1]);
  s1 = read_lines(file);
  file.close();
  // read second file
  file.open(argv[2]);
  s2 = read_lines(file);
  file.close();

  LCS<lines> lcs { s1, s2 };
  lcs.diff(std::cout);
}
