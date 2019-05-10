#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <cassert>
#include <algorithm>

class algorithm
{
  typedef std::vector<std::unordered_set<std::string>> cache;

  cache       m_cache; /* cache for DYNAMICPROGRAMMING!! */
  size_t      m_nstp;  /* maximal number of steps        */
  bool        m_uniq;  /* if all digits are unique       */
  std::string m_solu;  /* solution                       */

  /*
   * Mark step as completed.
   * If will some other path will lead to this step, it will stop at this poit.
   */
  void mark_step(size_t step, const std::string& str);

  /*
   * Check if step was previously marked.
   */
  bool is_old_step(size_t step, const std::string& str) const;

  /*
   * Algorithm itself.
   */
  void solve(size_t step, std::string& str);

  /*
   * Announce new solution.
   */
  void update_solution(const std::string& sol);

  algorithm(size_t nsteps, bool allunique);

  public:
  /*
   * Entry-point to the algorithm.
   */
  static std::string run(size_t nsteps, const std::string& str)
  {
    // check if all digits are unique
    int dc[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool uniq = true;
    for (auto c:str) {
      int idx = c - '0';
      if (dc[idx]++) {
        uniq = false;
        break;
      }
    }

    algorithm algo { nsteps, uniq }; // create environment
    auto buf = str; // copy initial string (`solve()` will mutate its argument)
    algo.solve(0, buf); // run algorithm

    return algo.m_solu;
  }
};

algorithm::algorithm(size_t nsteps, bool allunique)
: m_cache { 1 }, // dummy first element
  m_nstp { nsteps },
  m_uniq { allunique },
  m_solu { } // all possible inputs will be bigger than -1
{ }

void algorithm::mark_step(size_t step, const std::string& str)
{
  // expand vector for one more element
  if (step >= m_cache.size())
    m_cache.emplace_back();
  // save the step
  m_cache[step].insert(str);
}

bool algorithm::is_old_step(size_t step, const std::string& str) const
{
  // ignore requests for to high steps
  if (step >= m_cache.size())
    return false;
  // check if the same step is present
  auto sol = m_cache[step].find(str);
  return sol != m_cache[step].end();
}

void algorithm::solve(size_t step, std::string& str)
{
  // yield solution if number of steps reached the limit
  if (step == m_nstp) {
    update_solution(str);
    return;
  }
  
  if (is_old_step(step, str))
    return;

  mark_step(step, str);

  // perform all possible digit-swaps and repeat the algorithm for each of them
  bool branched = false; // true if any digit-swap succeed 
  for (auto i = 0; i < str.size(); ++i) {
    for (auto j = i + 1; j < str.size(); ++j) {
      if (str[i] < str[j]) { // swap ONLY if will move bigger digit to the "left"
        std::swap(str[i], str[j]); // "digit-swap"
        solve(step + 1, str);
        std::swap(str[i], str[j]); // resore the initial string
        branched = true;
      }
    }
  }

  if (!branched) {
    // If all the digits are unique and odd number of steps remains,
    // then solution will the string same to the current but with two last
    // digits swapped.
    // Otherwise, current string is the solution.
    if (m_uniq && ((m_nstp - step) & 0x01)) {
      auto len = str.size();
      std::swap(str[len-2], str[len-1]);
      update_solution(str);
      std::swap(str[len-2], str[len-1]);
    } else {
      update_solution(str);
    }
  }
}

void algorithm::update_solution(const std::string& sol)
{
  // final solution is the biggest one form all possible solutions
  m_solu = std::max(m_solu, sol);
}

int main()
{
  std::string s;
  size_t k;
  std::cin >> s >> k;
  auto sol = algorithm::run(k, s);
  std::cout << sol << std::endl;
}
