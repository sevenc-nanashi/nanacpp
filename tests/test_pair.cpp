#include "features/pair.hpp"

#include <cassert>

int main() {
  let p1 = hpair<int, int>(1, 2);
  let p2 = hpair<int, int>(1, 2);
  let p3 = hpair<int, int>(2, 3);

  assert(p1 == p2);
  assert(!(p1 == p3));

  std::unordered_set<hpair<int, int>> s;
  s.insert(p1);
  assert(s.size() == 1);
  assert(s.find(p2) != s.end());
  assert(s.find(p3) == s.end());

  s.insert(p3);
  assert(s.size() == 2);
}
