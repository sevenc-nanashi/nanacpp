#include "features/bisect.hpp"

#include <cassert>

int main() {
  auto first = bisect_first(0, 100, [](i64 x) { return x * x >= 2500; });
  assert(first == 50);

  auto last = bisect_last(0, 100, [](i64 x) { return x * x <= 2500; });
  assert(last == 50);

  auto first_negative = bisect_first(-5, 5, [](i64 x) { return x >= -2; });
  assert(first_negative == -2);

  auto last_negative = bisect_last(-5, 5, [](i64 x) { return x <= -2; });
  assert(last_negative == -2);

  auto first_not_found = bisect_first(-5, 5, [](i64 x) { return x > 5; });
  assert(first_not_found == 6);

  auto last_not_found = bisect_last(-5, 5, [](i64 x) { return x < -10; });
  assert(last_not_found == -6);

  return 0;
}
