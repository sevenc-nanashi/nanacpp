#include "features/rarray.hpp"
#include "features/rrange.hpp"

#include <cassert>
#include <stdexcept>
#include <string>

int main() {
  RArray<int> nums{1, 2, 3};

  assert(nums.size() == 3);
  assert(nums[0] == 1);
  assert(nums[2] == 3);
  assert(nums[-1] == 3);
  assert(nums[-3] == 1);

  nums[1] = 20;
  nums[-1] = 30;
  nums.push_back(40);
  assert((nums == std::vector<int>{1, 20, 30, 40}));

  const RArray<int> const_nums = nums;
  assert(const_nums[3] == 40);
  assert(const_nums[-1] == 40);
  assert(const_nums[-2] == 30);
  assert((nums[rrange(1, 2)] == RArray<int>{20, 30}));
  assert((nums[rexrange(1, 3)] == RArray<int>{20, 30}));
  assert((nums[rexrange(1, 4)] == RArray<int>{20, 30, 40}));
  assert((nums[rrange(-3, -1)] == RArray<int>{20, 30, 40}));
  assert((nums[rexrange(2, 2)] == RArray<int>{}));
  assert((const_nums[rrange(0, 1)] == RArray<int>{1, 20}));

  RArray<std::string> words(2, "x");
  words.emplace_back("y");
  assert(words[0] == "x");
  assert(words[2] == "y");
  assert(words[-1] == "y");

#ifndef ONLINE_JUDGE
  bool mutable_out_of_range = false;
  try {
    nums[nums.size()];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("RArray index out of range") != std::string::npos);
    assert(message.find("index=4") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
#if __cplusplus >= 202002L
    assert(message.find("tests/test_rarray.cpp") != std::string::npos);
#endif
    mutable_out_of_range = true;
  }
  assert(mutable_out_of_range);

  bool negative_out_of_range = false;
  try {
    nums[-5];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("RArray index out of range") != std::string::npos);
    assert(message.find("index=-5") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
#if __cplusplus >= 202002L
    assert(message.find("tests/test_rarray.cpp") != std::string::npos);
#endif
    negative_out_of_range = true;
  }
  assert(negative_out_of_range);

  bool const_out_of_range = false;
  try {
    const_nums[const_nums.size()];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("RArray index out of range") != std::string::npos);
    assert(message.find("index=4") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
#if __cplusplus >= 202002L
    assert(message.find("tests/test_rarray.cpp") != std::string::npos);
#endif
    const_out_of_range = true;
  }
  assert(const_out_of_range);

  bool range_out_of_range = false;
  try {
    nums[rrange(1, 4)];
  } catch (const std::out_of_range &error) {
    std::string message = error.what();
    assert(message.find("RArray index out of range") != std::string::npos);
    assert(message.find("index=4") != std::string::npos);
    assert(message.find("size=4") != std::string::npos);
#if __cplusplus >= 202002L
    assert(message.find("tests/test_rarray.cpp") != std::string::npos);
#endif
    range_out_of_range = true;
  }
  assert(range_out_of_range);
#endif

  return 0;
}
