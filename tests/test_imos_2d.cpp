#include "features/imos_2d.hpp"

#include <cassert>

int main() {
  Imos2D<int> imos(3, 4);
  imos.add(0, 0, 2, 3, 1);
  imos.add(1, 1, 3, 4, 2);

  const auto &values = imos.build();
  const vector<vector<int>> expected = {
      {1, 1, 1, 0},
      {1, 3, 3, 2},
      {0, 2, 2, 2},
  };
  assert(values == expected);
  assert(imos[1][2] == 3);

  Imos2D<long long> closed(2, 2);
  closed.add_closed(0, 0, 1, 1, 5);
  const auto &first = closed.build();
  assert(first == vector<vector<long long>>({{5, 5}, {5, 5}}));

  closed.add(0, 1, 2, 2, 2);
  const auto &second = closed.build();
  assert(second == vector<vector<long long>>({{5, 7}, {5, 7}}));

  vector<vector<long long>> base = {{10, 10}, {10, 10}};
  const auto applied = closed.applied(base);
  assert(applied == vector<vector<long long>>({{15, 17}, {15, 17}}));

  return 0;
}
