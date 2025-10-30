#include "features/core.hpp"

#include <cassert>

int main() {
  let data = vector<int>{1, 2, 3};
  assert(sz(data) == 3);

  int sum = 0;
  each(x, data) { sum += x; }
  assert(sum == 6);

  vector<int> doubled;
  enumerate(x, i, data) { doubled.push_back(x * static_cast<int>(i + 1)); }
  assert(doubled == vector<int>({1, 4, 9}));

  let data2 = vector<pair<int, int>>{{1, 10}, {2, 20}, {3, 30}};
  int total = 0;
  each2(x, y, data2) { total += x + y; }
  assert(total == 66);

  return 0;
}
