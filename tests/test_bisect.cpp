#include "features/bisect.hpp"

#include <cassert>
#include <vector>

int main() {
  std::vector<int> data{1, 3, 5, 7, 9};

  auto first_ge_five = bisect_first(0, static_cast<i64>(data.size()),
                                    [&](i64 idx) { return data[idx] >= 5; });
  assert(first_ge_five.has_value());
  assert(*first_ge_five == 2);

  auto none_ge_ten = bisect_first(0, static_cast<i64>(data.size()),
                                  [&](i64 idx) { return data[idx] >= 10; });
  assert(!none_ge_ten.has_value());

  auto first_closed =
      bisect_first_closed(0, 4, [&](i64 idx) { return idx >= 4; });
  assert(first_closed.has_value());
  assert(*first_closed == 4);

  auto last_le_five = bisect_last(0, static_cast<i64>(data.size()),
                                  [&](i64 idx) { return data[idx] <= 5; });
  assert(last_le_five.has_value());
  assert(*last_le_five == 2);

  auto none_negative = bisect_last(0, static_cast<i64>(data.size()),
                                   [&](i64 idx) { return data[idx] < 0; });
  assert(!none_negative.has_value());

  auto last_closed =
      bisect_last_closed(0, 4, [&](i64 idx) { return idx <= 4; });
  assert(last_closed.has_value());
  assert(*last_closed == 4);

  return 0;
}
