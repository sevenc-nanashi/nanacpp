#pragma once

#include "features/core.hpp"

/// ベクタ内の要素頻度を `std::map` で数える。
template <typename T> std::map<T, u64> tally(const std::vector<T> &data) {
  std::map<T, u64> counts;
  for (const auto &item : data) {
    counts[item]++;
  }
  return counts;
}
