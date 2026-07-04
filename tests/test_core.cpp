#include "features/core.hpp"

#include <cassert>

int main() {
  let data = Vec<int>{1, 2, 3};
  assert(sz(data) == 3);

  Vec<int> unsorted{3, 1, 2};
  std::sort(all(unsorted));
  assert((unsorted == Vec<int>{1, 2, 3}));
  std::sort(rall(unsorted));
  assert((unsorted == Vec<int>{3, 2, 1}));

  int best = 10;
  chmax(best, 20);
  assert(best == 20);
  chmin(best, 5);
  assert(best == 5);

  int sum = 0;
  each(x, data) { sum += x; }
  assert(sum == 6);

  Vec<int> doubled;
  enumerate(x, i, data) { doubled.push_back(x * static_cast<int>(i + 1)); }
  assert(doubled == Vec<int>({1, 4, 9}));

  let data2 = Vec<std::pair<int, int>>{{1, 10}, {2, 20}, {3, 30}};
  int total = 0;
  each2(x, y, data2) { total += x + y; }
  assert(total == 66);

  return 0;
}
