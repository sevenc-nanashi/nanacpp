#include "features/sum.hpp"

#include <cassert>

int main() {
  let nums = Vec<int>{1, 2, 3, 4};
  assert(sum<int>(nums) == 10);

  let empty_vec = Vec<int>{};
  assert(sum<long long>(empty_vec) == 0LL);

  let big_ints = Vec<int>{1'000'000'000, 1'000'000'000};
  assert(sum<long long>(big_ints) == 2'000'000'000LL);

  let negatives = std::array<int, 3>{-5, 10, -3};
  assert(sum<int>(negatives) == 2);

  let fractions = Vec<double>{0.5, 0.25, 0.75};
  assert(sum<double>(fractions) == 1.5);

  let init_list = {1, 2, 3};
  assert(sum<int>(init_list) == 6);

  return 0;
}
