#include "features/array_sum.hpp"

#include <cassert>

int main() {
  let data = vector<int>{1, 2, 3, 4, 5};
  ArraySum<int> arr_sum(data);

  assert(arr_sum.sum(0, 5) == 15);
  assert(arr_sum.sum(2, 4) == 7);
  assert(arr_sum.sum(1, 1) == 0);

  return 0;
}

