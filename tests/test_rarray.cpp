#include "features/rarray.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

int main() {
  RArray<int> nums{1, 2, 3};

  assert(nums.size() == 3);
  assert(nums[0] == 1);
  assert(nums[2] == 3);

  nums[1] = 20;
  nums.push_back(40);
  assert((nums == std::vector<int>{1, 20, 3, 40}));

  const RArray<int> const_nums = nums;
  assert(const_nums[3] == 40);

  RArray<std::string> words(2, "x");
  words.emplace_back("y");
  assert(words[0] == "x");
  assert(words[2] == "y");

#ifndef ONLINE_JUDGE
  bool mutable_out_of_range = false;
  try {
    nums[nums.size()];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("index=4") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
    assert(message.find("tests/test_backtrace_vec.cpp") != std::string::npos);
    mutable_out_of_range = true;
  }
  assert(mutable_out_of_range);

  bool const_out_of_range = false;
  try {
    const_nums[const_nums.size()];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("index=4") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
    assert(message.find("tests/test_backtrace_vec.cpp") != std::string::npos);
    const_out_of_range = true;
  }
  assert(const_out_of_range);
#endif

  return 0;
}
