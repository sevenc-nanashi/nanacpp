#include "features/array_sum.hpp"

#include <cassert>

int main() {
  let data = vector<int>{1, 2, 3, 4, 5};
  ArraySum<int> arr_sum(data);

  assert(arr_sum.sum(0, 5) == 15);
  assert(arr_sum.sum(2, 4) == 7);
  assert(arr_sum.sum(1, 1) == 0);

  assert(arr_sum.sum_closed(0, 4) == 15);
  assert(arr_sum.sum_closed(1, 3) == 9);
  assert(arr_sum.sum_closed(2, 2) == 3);

  return 0;
}
