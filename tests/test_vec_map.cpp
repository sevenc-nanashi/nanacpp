#include "features/vec_map.hpp"

#include <cassert>
#include <string>

int main() {
  let nums = vector<int>{1, 2, 3, 4};
  auto sq = vec_map<int>(nums, [](int x) { return x * x; });
  assert((sq == vector<int>{1, 4, 9, 16}));

  auto strs = vec_map<string>(nums, [](int x) { return to_string(x); });
  assert(strs.size() == nums.size());
  assert(strs.front() == "1");
  assert(strs.back() == "4");

  let empty = vector<int>{};
  auto empty_res = vec_map<int>(empty, [](int x) { return x; });
  assert(empty_res.empty());

  int acc = 0;
  auto prefix = vec_map<int>(nums, [&](int x) {
    acc += x;
    return acc;
  });
  assert((prefix == vector<int>{1, 3, 6, 10}));

  // in-place 変換
  auto inplace = nums;
  vec_map_inplace(inplace, [](int x) { return x * 2; });
  assert((inplace == vector<int>{2, 4, 6, 8}));

  vector<string> words{"abc", "de"};
  vec_map_inplace(words, [](const string &s) { return s + "!"; });
  assert((words == vector<string>{"abc!", "de!"}));

  vector<int> empty_vec;
  vec_map_inplace(empty_vec, [](int x) { return x + 1; });
  assert(empty_vec.empty());

  return 0;
}
