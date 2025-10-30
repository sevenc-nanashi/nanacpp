#pragma once

#include "features/core.hpp"

template <typename T> std::map<T, u64> tally(const std::vector<T> &data) {
  std::map<T, u64> counts;
  for (const auto &item : data) {
    counts[item]++;
  }
  return counts;
}

