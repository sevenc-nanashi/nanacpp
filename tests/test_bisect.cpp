#include "features/bisect.hpp"

#include <cassert>

int main() {
  auto first_open = bisect_first(0, 100, [](i64 x) { return x * x >= 2500; });
  assert(first_open == 50);

  auto first_open_not_found = bisect_first(-5, 5, [](i64 x) { return x > 5; });
  assert(first_open_not_found == 5);

  auto first_open_negative =
      bisect_first(-5, 6, [](i64 x) { return x >= -2; });
  assert(first_open_negative == -2);

  auto first_closed =
      bisect_first_closed(0, 100, [](i64 x) { return x * x >= 2500; });
  assert(first_closed == 50);

  auto first_closed_not_found =
      bisect_first_closed(-5, 5, [](i64 x) { return x > 5; });
  assert(first_closed_not_found == 6);

  auto last_open = bisect_last(0, 100, [](i64 x) { return x * x <= 2500; });
  assert(last_open == 50);

  auto last_open_negative =
      bisect_last(-5, 5, [](i64 x) { return x <= -2; });
  assert(last_open_negative == -2);

  auto last_open_not_found =
      bisect_last(-5, 5, [](i64 x) { return x < -10; });
  assert(last_open_not_found == -6);

  auto last_closed =
      bisect_last_closed(0, 100, [](i64 x) { return x * x <= 2500; });
  assert(last_closed == 50);

  auto last_closed_boundary =
      bisect_last_closed(0, 5, [](i64 x) { return x <= 5; });
  assert(last_closed_boundary == 5);

  auto last_closed_not_found =
      bisect_last_closed(-5, 5, [](i64 x) { return x < -10; });
  assert(last_closed_not_found == -6);

  return 0;
}
