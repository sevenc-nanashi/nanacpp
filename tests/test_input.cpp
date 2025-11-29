#include "features/input.hpp"
#include "features/pair.hpp"

#include <cassert>
#include <sstream>

int main() {
  std::stringstream ss;
  ss << "5 "
     << "1 2 3 4 5 "
     << "10 20 30 40 "
     << "7 8 "
     << "9 10 "
     << "11 12 13 14 15 16 "
     << "17 18 19 20";

  auto *orig = std::cin.rdbuf(ss.rdbuf());

  input(int, a);
  assert(a == 5);

  input_vec(int, vec, 5);
  assert(vec == vector<int>({1, 2, 3, 4, 5}));

  input_array(int, arr, 4);
  assert((arr == std::array<int, 4>{10, 20, 30, 40}));

  input_pair(int, int, p);
  assert((p == pair<int, int>(7, 8)));

  input_hpair(int, int, hp);
  assert((hp == hpair<int, int>(9, 10)));

  input_vec_pair(int, int, vp, 3);
  assert((vp == vector<pair<int, int>>({{11, 12}, {13, 14}, {15, 16}})));

  input_vec_hpair(int, int, vh, 2);
  assert((vh == vector<hpair<int, int>>({{17, 18}, {19, 20}})));

  std::cin.rdbuf(orig);
  return 0;
}
