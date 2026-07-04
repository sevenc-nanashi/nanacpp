#include "features/rrange.hpp"

#include <cassert>
#include <vector>

int main() {
  RRange<int> inclusive(1, 5);
  assert(inclusive.first() == 1);
  assert(inclusive.last() == 5);
  assert(!inclusive.exclude_last());
  assert(!inclusive.empty());
  assert(inclusive.size() == 5);
  assert(inclusive.include(1));
  assert(inclusive.include(3));
  assert(inclusive.include(5));
  assert(!inclusive.include(6));
  assert((inclusive.to_vec() == std::vector<int>{1, 2, 3, 4, 5}));

  std::vector<int> iterated;
  for (int value : inclusive) {
    iterated.push_back(value);
  }
  assert((iterated == std::vector<int>{1, 2, 3, 4, 5}));

  auto exclusive = RRange<int>::exclusive(1, 5);
  assert(exclusive.exclude_last());
  assert(!exclusive.empty());
  assert(exclusive.size() == 4);
  assert(exclusive.include(1));
  assert(exclusive.include(4));
  assert(!exclusive.include(5));
  assert((exclusive.to_vec() == std::vector<int>{1, 2, 3, 4}));

  auto same_inclusive = rrange(3, 3);
  assert(!same_inclusive.empty());
  assert(same_inclusive.size() == 1);
  assert((same_inclusive.to_vec() == std::vector<int>{3}));

  auto same_exclusive = rexrange(3, 3);
  assert(same_exclusive.empty());
  assert(same_exclusive.size() == 0);
  assert(!same_exclusive.include(3));
  assert(same_exclusive.to_vec().empty());

  RRange<int> descending(5, 1);
  assert(descending.empty());
  assert(descending.size() == 0);
  assert(!descending.include(3));
  assert(descending.to_vec().empty());

  RRange<int> negative(-2, 2);
  assert(negative.size() == 5);
  assert(negative.include(-1));
  assert((negative.to_vec() == std::vector<int>{-2, -1, 0, 1, 2}));

  assert(rrange(1, 5).overlaps(rrange(5, 8)));
  assert(rrange(1, 5).overlaps(rexrange(5, 8)));
  assert(rexrange(1, 5).overlaps(rrange(4, 8)));
  assert(!rexrange(1, 5).overlaps(rrange(5, 8)));
  assert(!rrange(1, 4).overlaps(rrange(5, 8)));
  assert(!rexrange(3, 3).overlaps(rrange(3, 5)));
  assert(!rrange(3, 5).overlaps(rexrange(3, 3)));

  return 0;
}
