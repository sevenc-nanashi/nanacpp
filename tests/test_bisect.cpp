#include "features/bisect.hpp"

#include <cassert>

int main() {
  auto first = bisect_first(0, 100, [](u64 x) { return x * x >= 2500; });
  assert(first == 50);

  auto last = bisect_last(0, 100, [](u64 x) { return x * x <= 2500; });
  assert(last == 50);

  auto first_false = bisect_first(0, 10, [](u64 x) { return x >= 10; });
  assert(first_false == 10);

  auto last_false = bisect_last(0, 10, [](u64 x) { return x <= 0; });
  assert(last_false == 0);

  return 0;
}

