#include "features/tally.hpp"

#include <cassert>

int main() {
  let data = vector<int>{3, 3, 1, 2, 3, 2};
  auto counts = tally(data);

  assert(counts.at(1) == 1);
  assert(counts.at(2) == 2);
  assert(counts.at(3) == 3);
  assert(counts.size() == 3);

  return 0;
}

