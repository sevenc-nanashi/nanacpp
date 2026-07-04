#include "features/rarray.hpp"
#include "features/rrange.hpp"

#include <cassert>
#include <stdexcept>
#include <string>
#include <type_traits>

template <typename Array, typename = void> struct HasSum : std::false_type {};

template <typename Array>
struct HasSum<Array, std::void_t<decltype(std::declval<Array>().sum())>>
    : std::true_type {};

template <typename Array, typename = void>
struct HasProduct : std::false_type {};

template <typename Array>
struct HasProduct<Array, std::void_t<decltype(std::declval<Array>().product())>>
    : std::true_type {};

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
  assert(nums.first().has_value());
  assert(*nums.first() == 1);
  assert(nums.last().has_value());
  assert(*nums.last() == 40);
  assert(nums.include(20));
  assert(!nums.include(100));
  assert(nums.count(20) == 1);
  assert((nums.take(2) == RArray<int>{1, 20}));
  assert((nums.drop(2) == RArray<int>{30, 40}));
  assert((nums.reverse() == RArray<int>{40, 30, 20, 1}));
  assert(nums.min().has_value());
  assert(*nums.min() == 1);
  assert(nums.max().has_value());
  assert(*nums.max() == 40);
  assert(nums.minmax().has_value());
  assert((*nums.minmax() == std::pair<int, int>{1, 40}));
  assert(nums.sum() == 91);
  assert(nums.product() == 24000);

  RArray<i64> longs{2, 3, 4};
  static_assert(HasSum<decltype(longs)>::value);
  static_assert(HasProduct<decltype(longs)>::value);
  assert(longs.sum() == 9);
  assert(longs.product() == 24);

  RArray<int> empty_nums;
  assert(!empty_nums.first().has_value());
  assert(!empty_nums.last().has_value());
  assert(!empty_nums.min().has_value());
  assert(!empty_nums.max().has_value());
  assert(!empty_nums.minmax().has_value());
  assert(empty_nums.sum() == 0);
  assert(empty_nums.product() == 1);

  RArray<std::string> words(2, "x");
  words.emplace_back("y");
  assert(words[0] == "x");
  assert(words[2] == "y");
  assert(words[-1] == "y");
  assert(words.count("x") == 2);
  assert(words.include("y"));
  assert((words.take(2) == RArray<std::string>{"x", "x"}));
  assert((words.drop(2) == RArray<std::string>{"y"}));
  assert((words.reverse() == RArray<std::string>{"y", "x", "x"}));
  assert(words.min().has_value());
  assert(*words.min() == "x");
  assert(words.max().has_value());
  assert(*words.max() == "y");
  static_assert(!HasSum<decltype(words)>::value);
  static_assert(!HasProduct<decltype(words)>::value);

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
