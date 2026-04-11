#include "features/key_packer.hpp"

#include <cassert>
#include <stdexcept>

int main() {
  KeyPacker<i64> packer{2, 3, 4};

  assert(packer.pack(0, 0, 0) == 0);
  assert(packer.pack(1, 0, 0) == 1);
  assert(packer.pack(0, 1, 0) == 3);
  assert(packer.pack(0, 0, 1) == 12);
  assert(packer.pack(2, 3, 4) == 59);

  assert((packer.pack(std::vector<i64>{2, 1, 3}) == 41));
  assert((packer.pack({1, 2, 3}) == 43));

  assert((packer.unpack(0) == std::vector<i64>{0, 0, 0}));
  assert((packer.unpack(43) == std::vector<i64>{1, 2, 3}));
  assert((packer.unpack(59) == std::vector<i64>{2, 3, 4}));

  const auto &limits = packer.limits();
  assert((limits == std::vector<i64>{2, 3, 4}));

  assert(packer.within_range(0, 0, 0));
  assert(packer.within_range(2, 3, 4));
  assert((packer.within_range(std::vector<i64>{1, 2, 3})));
  assert((packer.within_range({1, 2, 3})));
  assert(!packer.within_range(3, 0, 0));
  assert(!packer.within_range(-1, 0, 0));

  bool wrong_size_within_range = false;
  try {
    packer.within_range(1, 2);
  } catch (const std::invalid_argument &) {
    wrong_size_within_range = true;
  }
  assert(wrong_size_within_range);

  bool wrong_size = false;
  try {
    packer.pack(1, 2);
  } catch (const std::invalid_argument &) {
    wrong_size = true;
  }
  assert(wrong_size);

  bool too_large = false;
  try {
    packer.pack(3, 0, 0);
  } catch (const std::invalid_argument &) {
    too_large = true;
  }
  assert(too_large);

  bool negative_value = false;
  try {
    packer.pack(-1, 0, 0);
  } catch (const std::invalid_argument &) {
    negative_value = true;
  }
  assert(negative_value);

  bool negative_max = false;
  try {
    KeyPacker invalid{1, -1};
  } catch (const std::invalid_argument &) {
    negative_max = true;
  }
  assert(negative_max);

  bool negative_key = false;
  try {
    packer.unpack(-1);
  } catch (const std::invalid_argument &) {
    negative_key = true;
  }
  assert(negative_key);

  KeyPacker<int> int_packer{1, 1};
  assert(int_packer.pack(1, 1) == 3);
  assert((int_packer.unpack(2) == std::vector<int>{0, 1}));

  return 0;
}
