#include "features/imos.hpp"

#include <cassert>

int main() {
  Imos<int> imos(5);
  imos.add(1, 4, 2);
  imos.add(0, 2, 1);

  const auto &values = imos.build();
  assert(values == vector<int>({1, 3, 2, 2, 0}));
  assert(imos[3] == 2);

  Imos<long long> imos_closed(4);
  imos_closed.add_closed(1, 3, 5);
  const auto &closed = imos_closed.build();
  assert(closed == vector<long long>({0, 5, 5, 5}));

  imos_closed.add(0, 2, 3);
  const auto &updated = imos_closed.build();
  assert(updated == vector<long long>({3, 8, 5, 5}));

  vector<int> base = {10, 10, 10, 10, 10};
  const auto applied = imos.applied(base);
  assert(applied == vector<int>({11, 13, 12, 12, 10}));

  return 0;
}
