#include "features/cumulative_sum_2d.hpp"

#include <cassert>

int main() {
  vector<vector<int>> grid = {
      {1, 2, 3},
      {4, 5, 6},
      {7, 8, 9},
  };
  CumulativeSum2D<int> cs(grid);
  assert(cs.rows() == 3);
  assert(cs.cols() == 3);

  assert(cs.sum(0, 0, 3, 3) == 45);
  assert(cs.sum(0, 1, 2, 3) == 16);
  assert(cs.sum(1, 1, 3, 3) == 28);
  assert(cs.sum_closed(0, 0, 1, 1) == 12);
  assert(cs.sum_closed(2, 0, 2, 2) == 24);

  vector<vector<long long>> rect = {
      {10, -5},
      {3, 4},
      {7, 1},
  };
  CumulativeSum2D<long long> cs_rect(rect);
  assert(cs_rect.sum_closed(1, 0, 2, 1) == 15);
  assert(cs_rect.sum(0, 0, 0, 0) == 0);

  return 0;
}
